import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from decimal import Decimal

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Query the database for the activity of the user currently logged in
    activityRows = db.execute("SELECT * FROM activity WHERE user_id = ?", session["user_id"])

    # Get the number of rows the above query returned
    numOfRows = len(activityRows)

    # Check if the number of rows returned is greater than 0
    if numOfRows > 0:

        # Query the database for the cash of the user
        cashList = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cashList[0]["cash"]

        # Get all the stocks the user has so: Query the database for the stock symbol and company name to display on the page
        viewRowLists = db.execute("SELECT stock_symbol, company_name FROM stocks JOIN activity ON stocks.id = activity.stock_id WHERE user_id = ? GROUP BY activity.stock_id HAVING SUM(shares) > ?", session["user_id"], 0)

        # Query the database for all the stocks the user has
        symbolList = db.execute("SELECT stock_symbol FROM stocks WHERE id IN (SELECT stock_id FROM activity WHERE user_id = ? ORDER BY id DESC)", session["user_id"])

        # Update the current price of each stock the user has
        for o in symbolList:
            for key in o:
                symbol = o[key]
                result = lookup(symbol)
                priceUpdate = result["price"]
                db.execute("UPDATE stocks SET current_stock_price = ? WHERE stock_symbol = ? AND id IN (SELECT stock_id FROM activity WHERE user_id = ?)", priceUpdate, symbol, session["user_id"])

        # Get the current price of each stocks and the sum of shares of each stock the user has
        updatedValues = db.execute("SELECT current_stock_price, SUM(shares) As sum FROM stocks JOIN activity ON stocks.id = activity.stock_id WHERE user_id = ? GROUP BY activity.stock_id HAVING SUM(shares) > ?", session["user_id"], 0)

        # Get the current total value of each holding of the user by multiplying the current price with the sum of shares of that stock
        # do this for each stock hence the loop
        product = 1
        listOfProduct = []
        # Multiply Items
        for j in updatedValues:
            for key in j:
                product = product * j[key]
            listOfProduct.append(product)
            product = 1

        # sum the total value of all the stock the user has
        total = sum(listOfProduct)

        # Calculate the grand total value by adding the cash the user has with the total value of each holding
        grandTotal = cash + total

        # Update the grand total of the user in the user_stock_value table: it was made to keep track of the uusers grand total
        db.execute("UPDATE user_stocks_value SET grand_total = ? WHERE id = ?", grandTotal, session["user_id"])

        return render_template("index.html", cash=cash, grandTotal=grandTotal, numOfRows=numOfRows, combination=zip(viewRowLists, updatedValues))

    else:
        return render_template("index.html", numOfRows=numOfRows)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # Get the symbol inputted by the user
        symbol = request.form.get("symbol")

        # Get the stock quote for a company using the company's stock symbol
        stock = lookup(symbol)

        userid = session["user_id"]

        # Ensure symbol was submitted and the user submits a valid stock symbol
        if not symbol or stock == None:
            return apology("Please enter a symbol", 400)

        # Get the name the name of the company and the price of the stock from the result of lookup
        name = stock["name"]
        price = stock["price"]

         # Get the number of shares inputted by the user
        shares = request.form.get("shares")

        # Ensure the user submits an integer not an alphabet or character
        if shares.isnumeric() == False:
            return apology("Please enter the amount shares,", 400)

        # Ensure shares was submitted and the number of shares is not zero or a negative number
        if not shares or int(shares) <= 0:
            return apology("Please enter the am of shares,", 400)

        # Convert the number from the shares field which is a string to an integer
        numOfShares = int(shares)

        # Query the database for cash the user that is currently logged in has
        cashList = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cashList[0]["cash"]

        # Ensure the user has enough money to buy shares
        if cash > (price * numOfShares):

            # Get the total value of each holding
            value = stock["price"] * int(shares)

            # Calculate the cash the user currently has after buying shares
            updatedCash = cash - value

            # Update the cash column for the user currently logged in with the cash the user currently has
            db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedCash, session["user_id"])

            # Query the database for all the stocks already in the database
            symbolList = db.execute("SELECT stock_symbol FROM stocks")

            # Insert into the stocks table if the stock which the user want to buy isn't already in the database
            # because i created a unique index on the stock_symbol
            if not any(dic['stock_symbol'] == symbol for dic in symbolList):
                db.execute("INSERT INTO stocks (stock_symbol, company_name, current_stock_price) VALUES (?, ?, ?)", symbol, name, price)

            # Query the database for the id of that particular stock the user wants to buy
            stockIdList = db.execute("SELECT id FROM stocks WHERE stock_symbol = ?", symbol)

            # insert the purchase activity into the activity table which includes the user_id which corresponds to the id of the user currently
            # logged in, the stock id which corresponds to the id of stock the user just purchased, the number of shares the user bought,
            # the price of that stock and the total value of each holding
            db.execute("INSERT INTO activity (user_id, stock_id, shares, price, total_value) VALUES (?, ?, ?, ?, ?)", userid, stockIdList[0]["id"], numOfShares, price, value)
            return redirect("/")

         # User reached route via GET (as by clicking a link or via redirect)
        else:
            return apology("You don't have enough money to buy this amount", 400)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM activity WHERE user_id = ?", session["user_id"])
    numOfRows = len(rows)
    if numOfRows > 0:
        histories = db.execute("SELECT stock_symbol, shares, price, date FROM stocks JOIN activity ON stocks.id = activity.stock_id WHERE activity.user_id = ?", session["user_id"])
        return render_template("history.html", histories=histories, numOfRows=numOfRows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        # Get the symbol from the input field
        symbol = request.form.get("symbol")

        # Ensure symbol was submitted
        if not symbol:
            return apology("Please enter a symbol")

        # Get the stock quote for a company using the company's stock symbol
        results = lookup(symbol)

        # Ensure the user submits a valid stock symbol
        if results == None:
            return apology("Please enter a symbol")

        # Pass the result of lookup into qouted.html
        return render_template("quoted.html", results=results)

    # user reached route via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")
        names = db.execute("SELECT username FROM users")

        # Ensure user name was submitted
        if not username:
            return apology("Please enter another username", 400)


        # Query database for username
        usernameList = db.execute("SELECT username FROM users")

        # Check if username exists in database
        if any(dic['username'] == username for dic in usernameList):
            return apology("Please enter another username", 400)

        # Get the inputted passwords from the two password fields
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure password was submitted
        if not password or password != confirmation:
            return apology("Please make sure the passwords match", 400)

        """My personal touch: Require users’ passwords to have some number of letters, numbers, and/or symbols.
        But check50 throwing registration errors so i decided to comment it out. To try this feature, you can
        uncomment"""

        # specialChar = ['^', '%', '/', '#', '@' ]

        # if len(password) < 10 or len(password) > 20:
        #     return apology("Please make sure your password is between 10-25 character long", 403)

        # if not any(character.isdigit() for character in password):
        #     return apology("Please make sure your password contains at least a number", 403)

        # if not any(character in specialChar for character in password):
        #     return apology("Please make sure your password contains any of these symbols: ^, %, /, #, @", 403)

        # Generate a hash password
        hashPassword = generate_password_hash(password)

        # Insert the new user into the database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashPassword)

        # Redirect the user to the log in page
        return redirect("/login")

    # user reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # lot = []

    if request.method == "POST":

        # Get the symbol inputted by the user
        symbol = request.form.get("symbol")

        # Ensure symbol was submitted
        if not symbol:
            return apology("Please select a symbol", 400)

        # Get the stock quote for a company using the company's stock symbol
        stock = lookup(symbol)
        name = stock["name"]
        price = stock["price"]

        userid = session["user_id"]

        # Query the database to get the id of the stock that the user wants to sell
        symbolIdList = db.execute("SELECT id FROM stocks WHERE stock_symbol = ?", symbol)
        symbolId = symbolIdList[0]["id"]

        # Query the database for the sum of shares the user has of the stock he/she wants to sell
        totalStockSharesList = db.execute("SELECT sum(activity.shares) FROM stocks JOIN activity ON stocks.id = activity.stock_id WHERE activity.stock_id = ? AND activity.user_id = ?", symbolId, session["user_id"])
        totalStockShares = totalStockSharesList[0]["sum(activity.shares)"]

        # Get the number of shares the user inputted
        shares = request.form.get("shares")

        # Ensure shares was submitted and the user has up to that number of shares he/she inputted and also the user doesn't
        # input zero or a negative number
        if not shares or int(shares) > totalStockShares or int(shares) <= 0 or totalStockShares <= 0:
            return apology("Not enough shares", 400)

        # Convert the number of shares the user inputted into a negative integer since the user is selling in order to insert
        # it into the database
        numOfShares = -int(shares)

        # Calculate the total value of the stock by multiplying the price of the stock and the remaining shares of that stock
        value = stock["price"] * int(shares)

        # Query the database for the cash the user has
        cashList = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cashList[0]["cash"]

        # Calculate the updated amount of cash the user has
        updatedCash = cash + value

        #  Update the cash column with the updated amount of cash the user has
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedCash, session["user_id"])

       # Insert the selling activity into the activity table which includes the user_id which corresponds to the id of the user currently
       # logged in, the stock id which corresponds to the id of stock the user just purchased, the number of shares the user bought,
       # the price of that stock and the total value of each holding
        db.execute("INSERT INTO activity (user_id, stock_id, shares, price, total_value) VALUES (?, ?, ?, ?, ?)", userid,  symbolId, numOfShares, price, value)


        return redirect("/")

     # user reached route via GET
    else:
        
        Query the database for all the stock symbol in order to pass it into the select options as long as the sum of the shares
        selectOptions = db.execute("SELECT stock_symbol FROM stocks JOIN activity ON stocks.id = activity.stock_id WHERE user_id = ? GROUP BY activity.stock_id HAVING SUM(shares) > ?", session["user_id"], 0)

        return render_template("sell.html", symbs=selectOptions)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
