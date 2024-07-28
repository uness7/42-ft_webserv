#!/usr/bin/env python3

import os
import cgi
import cgitb

cgitb.enable();

form = cgi.FieldStorage();

file_item = form['file']


print(file_item.filename);


if file_item.filename:
    fn = os.path.basename(file_item.filename)
    with open('files/' + fn, 'wb') as f:
        for chunk in fbuffer(file_item.file):
            f.write(chunk)
    message = f'The file "{fn}" was uploaded successfully'
else:
    message = 'No file was uploaded'
    print(f"Content-Type: text/html\n\n<html><body><p>{message}</p></body></html>")
