import cgi

form = cgi.FieldStorage()

# Output values
name = form.getvalue('name')
status = form.getvalue('status')
age = form.getvalue('age')
email = form.getvalue('email')
feedback = form.getvalue('feedback')

# Get selected colors (returns a list)
colors = form.getlist('colors')
country = form.getvalue('country')

# Print the response with CSS styles
print(
f"""
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Form Submission Response</title>
    <style>
        body {{
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            color: #333;
            text-align: center;
            padding: 20px;
        }}
        h1 {{
            color: #4CAF50;
        }}
        p {{
            background-color: #ffffff;
            border: 1px solid #ddd;
            border-radius: 5px;
            padding: 10px;
            margin: 10px auto;
            width: 60%;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
        }}
        .container {{
            max-width: 800px;
            margin: auto;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>Received Form Data:</h1>
        <p><strong>Name:</strong> {name}</p>
        <p><strong>Status:</strong> {status}</p>
        <p><strong>Age:</strong> {age}</p>
        <p><strong>Email:</strong> {email}</p>
        <p><strong>Feedback:</strong> {feedback}</p>
        <p><strong>Favorite Colors:</strong> {', '.join(colors)}</p>
        <p><strong>Country:</strong> {country}</p>
    </div>
</body>
</html>
"""
)

