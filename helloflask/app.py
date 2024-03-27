from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html")

    print("Form submitted!")
    color = request.form.get("color")

    if color not in ["red", "blue"]:
        return render_template("failure.html", color=color)

    return render_template("color.html", color=color)