#!/usr/bin/env python3

import os
import cgi
import cgitb

cgitb.enable();

form = cgi.FieldStorage();


 # Print the form data for debugging
print("<html><body>")
print("<h1>Form Data</h1>")
print("<table border='1'>")
print("<tr><th>Field Name</th><th>Value</th></tr>")

    # Get the list of form fields and their values
for key in form.keys():
    value = form.getvalue(key)
    print(f"<tr><td>{key}</td><td>{value}</td></tr>")

print("</table>")
print("</body></html>")

"""

if file_item.filename:
    fn = os.path.basename(file_item.filename)
    with open('files/' + fn, 'wb') as f:
        for chunk in fbuffer(file_item.file):
            f.write(chunk)
    message = f'The file "{fn}" was uploaded successfully'
else:
    message = 'No file was uploaded'
    print(f"Content-Type: text/html\n\n<html><body><p>{message}</p></body></html>")

"""
