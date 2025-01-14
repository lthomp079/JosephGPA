"""
    Made by Lucas Thompson on Github.
    https://github.com/lthomp079/JosephGPA
    Copyright 2025 Lucas B. Thompson under the Apache 2.0 License
"""

from flask import Flask, render_template, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')
"""
@app.route('/hawks')
def slope():
    return render_template('hawks.html')
"""
@app.route('/submit', methods=['POST'])
def submit():
    grades = request.form['grades']

    send = grades.split(",")
    formatted_grades = ' '.join(grade.strip() for grade in send)
    command = ["./test"] + formatted_grades.split()
    result = subprocess.run(command, capture_output=True, text=True)
    output = result.stdout

    print("C++ Output:", output)  # Debug line

    # Handle errors from the C++ program
    if result.returncode == 1:
        return jsonify({"error": "Your grade has to be.. only numbers!!"})

    if result.returncode == 3:
        return jsonify({"error": "You know you can't have a number higher than 115... We all know you aren't THAT smart..."})

    if result.returncode == 4:
        return jsonify({"error": "How did you even get to more than one period????"})

    if result.returncode == 5:
        return jsonify({"error": "Did you really expect it to work? You have no numbers......"})



    # Format output for HTML
    formatted_output = []
    for line in output:
        # Replace '\n' with '<br>' and '\t' with '&nbsp;&nbsp;&nbsp;&nbsp;' for HTML formatting
        formatted_line = line.replace('\n', '<br>').replace('\t', '&nbsp;&nbsp;&nbsp;&nbsp;')
        formatted_output.append(formatted_line)

    formatted_output = ''.join(formatted_output)

    # Return the formatted output as a JSON response
    return jsonify({
        'output': formatted_output
    })

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True)
