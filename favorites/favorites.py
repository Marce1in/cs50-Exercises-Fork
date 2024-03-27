from cs50 import SQL

db = SQL("sqlite:///favorites.db")

titles = db.execute("SELECT title FROM shows")
print(titles)
for name in titles:
    if name['title'].istitle() == False:
        db.execute("UPDATE shows SET title = ? WHERE title = ?", name['title'].title(), name['title'])
