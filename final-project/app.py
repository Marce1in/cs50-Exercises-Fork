from cs50 import SQL
from flask import Flask, render_template, request, session, redirect, jsonify
from flask_session import Session
from helpers import login_required
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

app = Flask(__name__)
app.secret_key = "CS50 super secret key"

db = SQL("sqlite:///task.db")

# Log the user in
@app.route("/login", methods=["GET", "POST"])
def login():

    session.clear()
    error = None

    if request.method == "POST":

        # Check if user input is valid
        if not request.form.get("username"):
            error="Blank names are not allowed!"

        elif not request.form.get("password"):
            error="Blank passwords are not allowed!"

        try:
            user = db.execute("SELECT * FROM users WHERE name = ?",
                        request.form.get('name'))[0]
        except IndexError:
            error="Invalid username and/or password"
            return render_template('login.html', error=error)

        if not check_password_hash(user["hash"], request.form.get("password")):
            error="Invalid username and/or password"
            return render_template('login.html', error=error)

        # Log the user in
        session["user_id"] = user["id"]

        return redirect("/")

    return render_template('login.html', error=error)


# Register a new user
@app.route("/register", methods=["GET", "POST"])
def register():

    error = None

    if request.method == "POST":

        # Check if user input is valid
        username = request.form.get('name')
        if username == "":
            error = "Blank names are not allowed!"
            return render_template("register.html", error=error)

        elif len(username) > 20:
            error = "Name longer than 20 characters are not allowed!"
            return render_template("register.html", error=error)

        elif db.execute("SELECT name FROM users WHERE name = ?",
                        username) != []:
            error = "Sorry, this username is already in use :("
            return render_template("register.html", error=error)


        password = request.form.get('password1')
        if password == "":
            error = "Blank passwords are not allowed!"
            return render_template("register.html", error=error)

        elif len(password) > 30:
            error = "Password longer than 30 characters are not allowed!"
            return render_template("register.html", error=error)

        elif password != request.form.get('password2'):
            error = "Your passwords don't match!"
            return render_template("register.html", error=error)

        # Hash the password
        hash = generate_password_hash(password)

        # Create a new user in the database
        db.execute("INSERT INTO users (name,hash) VALUES (?,?)",
                   username, hash)

        return redirect("/login")

    return render_template("register.html", error=error)

# Get the currently day of the week
@app.route("/")
@login_required
def week():
   dt = datetime.now()
   day = dt.isoweekday()
   return redirect(f"/{day}")

# Load all the tasks that are linked with the choosed day
@app.route("/<id>")
@login_required
def home(id):

    # Check if the id is valid
    try:
        id = int(id)
    except ValueError:
        id = 1
    if id < 1 or id > 7:
        id = 1

    # Get the user tasks
    tasks = db.execute("SELECT * FROM tasks WHERE user_id = ? AND week = ? ORDER BY date ASC", session["user_id"], id)

    return render_template('index.html', tasks=tasks, day=id)

# Create a new task in the database
@app.route("/create", methods=["POST"])
@login_required
def create():

    # Get user data
    data = request.get_json()
    name, date, day, id = data['name'], data['date'], data['day'], session['user_id']

    # Check if user input is valid
    if len(name) > 20:
        name = name[:20]
    elif name == "":
        name = "Task"

    if date != "":
        if date[2] != ":":
            date = ""
        elif not date[:2].isdigit() or not date[3:].isdigit():
            date = ""

    try:
        day = int(day)
    except ValueError:
        day = 1
    if day < 1 or day > 7:
        day = 1

    # Create a new task on the database
    db.execute("INSERT INTO tasks (name, date, week, user_id) VALUES (?,?,?,?)",
               name, date, day, id)

    # Get the ID of this new task
    task_id = db.execute("SELECT id FROM tasks WHERE user_id = ? ORDER BY id DESC LIMIT 1", id)[0]['id']

    # Send back the id for the HTML
    return jsonify({'task_id': task_id}), 200

# Check if the user is the real owner of the task
def task_own():
    task_user_id = db.execute("SELECT user_id FROM tasks WHERE id = ?", request.get_json()["id"])
    if task_user_id[0]["user_id"] != session['user_id']:
        return False
    else:
        return True

# Edit the task in the database
@app.route("/edit", methods=["PUT"])
@login_required
def edit():

    if task_own() == False:
        return jsonify({'status': 'failure'}), 401

    # Get user data
    data = request.get_json()
    name, date, id = data['name'], data['date'], data['id']


    # Check if user input is valid
    if len(name) > 20:
        name = name[:20]

    if date != "":
        if date[2] != ":":
            date = ""
        elif not date[:2].isdigit() or not date[3:].isdigit():
            date = ""

    # Edit the task name and the date if necessary
    if date != "":
        db.execute("UPDATE tasks SET date = ? WHERE id= ?", date, id)
    if name != "":
        db.execute("UPDATE tasks SET name = ? WHERE id= ?", name, id)

    return jsonify({'status': 'success'}), 200

# Conclude the task in the database
@app.route("/conclude", methods=["PUT"])
@login_required
def conclude():

    if task_own() == False:
        return jsonify({'status': 'failure'}), 401

    # Get the task id from the user
    id = str(request.get_json()['id'])

    # Get the state of the task
    task_state = db.execute("SELECT state FROM tasks WHERE id = ?", id)

    # If the task is concluded in the database, then undo, else conclude
    if task_state[0]["state"] == 1:
        db.execute("UPDATE tasks SET state = ? WHERE id = ?", 0, id)
    else:
        db.execute("UPDATE tasks SET state = ? WHERE id = ?", 1, id)

    return jsonify({'status': 'success'}), 200

# Delete the task in the database
@app.route("/delete", methods=["DELETE"])
@login_required
def delete():

    if task_own() == False:
        return jsonify({'status': 'failure'}), 401

    # Get the task id from the user
    id = str(request.get_json()['id'])

    # Delete the task from the database
    db.execute("DELETE FROM tasks WHERE id = ?", id)

    return jsonify({'status': 'success'}), 200

# Delete ALL the tasks of a day in the database
@app.route("/deleteall", methods=["DELETE"])
@login_required
def deleteall():

    # Get the day of the week from the user
    day = str(request.get_json()['day'])

    # Get delete all the tasks of this day
    db.execute("DELETE FROM tasks WHERE week = ? AND user_id = ?", day, session['user_id'])

    return jsonify({'status': 'success'}), 200
