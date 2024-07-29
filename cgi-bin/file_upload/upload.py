#!/usr/bin/env python3

import os
import cgi
import cgitb

cgitb.enable()


form = cgi.FieldStorage()

for key in form.keys():
    print(f"{key}: {form[key]}")

file_item = form['file']

if file_item.file:
    message = f'The file "{fn}" was uploaded successfully'
else:
    message = 'No file was uploaded'

print(f"Content-Type: text/html\n\n<html><body><p>{message}</p></body></html>")

