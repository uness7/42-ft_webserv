#!/usr/bin/env python3

# Importing the 'cgi' module
import cgi

# Send an HTTP header indicating the content type as HTML
print("Content-Type: text/html\n")  # Ensure single newline after headers

# Start an HTML document with center-aligned content
print("<html><body style='text-align:center;'>")

# Display a green heading with text "GeeksforGeeks"
print("<h1 style='color: green;'>GeeksforGeeks</h1>")

# Parse form data submitted via the CGI script
form = cgi.FieldStorage()

# Check if the "name" field is present in the form data
if "name" in form:
    # If present, retrieve the value and display a personalized greeting
    name = form.getvalue("name")
    print("<h2>Hello, " + name + "!</h2>")
    print("<p>Thank you for using our script.</p>")
else:
    print("<p>No name recorded</p>")

# Check if the "happy" checkbox is selected
if "happy" in form:
    # If selected, display a message with a happy emoji
    print("<p>Yayy! We're happy too! 😊</p>")
else:
    print("<p>No value recorded</p>")

# Check if the "sad" checkbox is selected
if "sad" in form:
    # If selected, display a message with a sad emoji
    print("<p>Oh no! Why are you sad? 😢</p>")

# Close the HTML document
print("</body></html>")

