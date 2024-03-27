import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get the username and the cash
    user = db.execute("SELECT username, cash FROM users WHERE id = ?", session["user_id"])
    # Get all user's stocks history
    stocks = db.execute("SELECT symbol, shares FROM stocks WHERE user = ?", user[0]["username"])

    # {Symbol: [price, shares, total]}
    total = {}

    # Populate the dict with all the user stocks
    for stock in stocks:
        if stock["symbol"] not in total.keys():
            total[stock["symbol"]] = [lookup(stock["symbol"])["price"], stock["shares"], 0]

        else:
            total[stock["symbol"]][1] += stock["shares"]

    # Delete all the stocks that are zero or less
    for symbol in total.copy():

        if total[symbol][1] <= 0:
            del total[symbol]
        else:  # Also calculate the total money that the user has invested in a stock
            total[symbol][2] = total[symbol][0] * total[symbol][1]

    # Save the user money in a variable
    user_cash = user[0]["cash"]

    # Create a variable that will sum the user money with all the money that he have in stocks
    sum_cash = user_cash
    for symbol in total:

        sum_cash += total[symbol][2]

    # Change all the monetary values inside the "total" dict to USD
    for symbol in total:

        total[symbol][0], total[symbol][2] = usd(total[symbol][0]), usd(total[symbol][2])

    return render_template("index.html", stocks=total, cash=usd(user_cash), sum_cash=usd(sum_cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        # Check if the user input value is valid
        symbol = request.form.get("symbol")
        if symbol == "":
            return apology("Blank symbol")
        # {'name': 'foo', 'price': 'bar', 'symbol': 'baz'}
        symbol = lookup(symbol)
        if symbol == None:
            return apology("Invalid symbol")

        # Check if the user input value is valid
        shares = request.form.get("shares")

        if not shares.isdigit():
            return apology("This is not a valid number you silly ;)")

        shares = int(shares)

        if shares <= 0:
            return apology("invalid number")

        # Get the user name and the user cash from the database
        user_info = db.execute("SELECT cash, username FROM users WHERE id = ?",
                               session["user_id"])

        # Calculate how much will cost
        price = symbol["price"] * shares

        # Check if the user has enought money
        if price > user_info[0]["cash"]:
            return apology("Insufficient money")

        # Update the user money
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   (user_info[0]["cash"] - price), session["user_id"])

        # Register the purchase in the database
        db.execute("INSERT INTO stocks (user,shares,symbol,price) VALUES (?,?,?,?)",
                   user_info[0]["username"], shares, symbol["symbol"], symbol["price"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get the username
    user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])

    # Get ALL the user's stock history
    stocks = db.execute("SELECT symbol, shares, price, dates FROM stocks WHERE user = ?", user[0]["username"])

    # Change the monetary values to USD
    for stock in stocks:
        stock["price"] = usd(stock["price"])

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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
    if request.method == "POST":

        # Check if the quote is valid
        quote = request.form.get("symbol")
        if quote == "":
            return apology("Missing symbol")

        # Get the price the name and the symbol of a quote in a dict
        # {'name': 'foo', 'price': '0.00', 'symbol': 'baz'}
        quote = lookup(quote)
        # Check if the lookup as sucessfull
        if quote == None:
            return apology("Symbol not found")

        # Show the quote to the user
        return render_template("quoted.html", name=quote["name"], price=usd(quote["price"]), symbol=quote["symbol"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Get the name and check if is not blank or invalid
        username = request.form.get("username")

        if username == "":
            return apology("user's input is blank")

        if db.execute("SELECT username FROM users WHERE username = ?",
                      username) != []:
            return apology("Sorry! This name is already in use :(")

        # Check if the password is valid and match
        password = request.form.get("password")

        if password == "":
            return apology("user's input is blank")

        if password != request.form.get("confirmation"):
            return apology("Passwords don't match")

        # Hash the passaword
        hash = generate_password_hash(password)

        # Insert the user name and the passoword into the database
        db.execute("INSERT INTO users (username,hash) VALUES (?,?)",
                   username, hash)

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get the username and the cash
    user = db.execute("SELECT username, cash FROM users WHERE id = ?", session["user_id"])
    # Get all user's stocks history
    stocks = db.execute("SELECT symbol, shares FROM stocks WHERE user = ?", user[0]["username"])

    # {Symbol: [shares]}
    total = {}

    # Populate the dict with all the user stocks
    for stock in stocks:

        if stock["symbol"] not in total.keys():
            total[stock["symbol"]] = stock["shares"]

        else:
            total[stock["symbol"]] += stock["shares"]

    if request.method == "POST":

        # Check if the symbol is valid
        symbol = request.form.get("symbol")
        if symbol not in total.keys():
            return apology("Invalid symbol")

        # Check if the shares number to sell is valid
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Invalid number")

        if shares < 1 or shares > total[symbol]:
            return apology("Invalid number")

        # Get the current value of the chosen symbol and
        symbol = lookup(symbol)

        # Register the user sold stocks
        db.execute("INSERT INTO stocks (user,shares,symbol,price) VALUES (?,?,?,?)",
                   user[0]["username"], (shares * -1), symbol["symbol"], symbol["price"])

        # Update user's cash
        user_cash = user[0]["cash"] + (shares * symbol["price"])

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user_cash, session["user_id"])

        return redirect("/")

    else:
        # Delete all the stocks that are zero or less
        for stock in total.copy():
            if total[stock] <= 0:
                del total[stock]

        return render_template("sell.html", stocks=total)


@app.route("/money", methods=["POST"])
@login_required
def money():
    # Get the user currently money
    usr_money = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # Get the extra cash that the user is adding to his account and check if it's a number
    try:
        ext_cash = float("%.2f" % float(request.form.get("cash").replace(",", ".")))
    except ValueError:
        return apology("if the problem persist, try to stop using dots or commas!", "Sorry, this is not a number")

    # Check if the value is valid
    if ext_cash <= 0:
        return apology("Sorry, just positive numbers")

    # Update the user money in the database
    usr_money += ext_cash
    db.execute("UPDATE users SET cash = ? WHERE id = ?",
               usr_money, session["user_id"])

    return redirect("/")
