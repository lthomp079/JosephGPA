"""
    Made by Lucas Thompson on Github.
    https://github.com/lthomp079/JosephGPA
    Copyright 2025 Lucas B. Thompson under the Apache 2.0 License
"""

from flask import Flask, render_template, request, jsonify, send_from_directory
import subprocess

app = Flask(__name__)

@app.route('/favicon.ico')
@app.route('/construct')
@app.route('/robots.txt')
@app.route('/sitemap.xml')
def robotAndSitemap():
	return send_from_directory(app.static_folder, request.path[1:])

@app.route('/')
def index():
    return render_template('index.html')


@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/submit', methods=['POST'])
def submit():
    grades = request.form['grades']
    weights = request.form.get('weights', '')  # Get weights if provided
    
    send = grades.split(",")
    formatted_grades = ' '.join(grade.strip() for grade in send)
    command = ["./Calculate.exe"] + formatted_grades.split()
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

    # Process grades and weights to create detailed results
    grade_values = [float(grade.strip()) for grade in send]
    
    # Process weights if provided
    weight_values = []
    if weights:
        weight_values = [float(weight.strip()) for weight in weights.split(",")]
    else:
        weight_values = [0.0] * len(grade_values)  # Default to no weights
        
    # Calculate detailed results
    detailed_results = []
    total_unweighted_gpa = 0
    total_weighted_gpa = 0
    
    for i, grade in enumerate(grade_values):
        # Get the letter grade and GPA
        letter = ""
        unweighted_gpa = 0.0
        
        # Letter grade calculation based on Calculate.cpp logic
        if grade >= 92.5 and grade < 115:
            letter = "A"
            unweighted_gpa = 4.0
        elif grade >= 89.5 and grade < 92.5:
            letter = "A-"
            unweighted_gpa = 3.7
        elif grade >= 86.5 and grade < 89.5:
            letter = "B+"
            unweighted_gpa = 3.3
        elif grade >= 82.5 and grade < 86.5:
            letter = "B"
            unweighted_gpa = 3.0
        elif grade >= 79.5 and grade < 82.5:
            letter = "B-"
            unweighted_gpa = 2.7
        elif grade >= 76.5 and grade < 79.5:
            letter = "C+"
            unweighted_gpa = 2.3
        elif grade >= 72.5 and grade < 76.5:
            letter = "C"
            unweighted_gpa = 2.0
        elif grade >= 69.5 and grade < 72.5:
            letter = "C-"
            unweighted_gpa = 1.7
        elif grade >= 66.5 and grade < 69.5:
            letter = "D+"
            unweighted_gpa = 1.3
        elif grade >= 62.5 and grade < 66.5:
            letter = "D"
            unweighted_gpa = 1.0
        else:
            letter = "F"
            unweighted_gpa = 0.0
            
        # Calculate weighted GPA
        weight = weight_values[i] if i < len(weight_values) else 0.0
        weighted_gpa = unweighted_gpa + weight
        
        # Add to totals
        total_unweighted_gpa += unweighted_gpa
        total_weighted_gpa += weighted_gpa
        
        # Add to detailed results
        detailed_results.append({
            "grade": round(grade, 1),
            "letter": letter,
            "unweightedGPA": round(unweighted_gpa, 2),
            "weightedGPA": round(weighted_gpa, 2)
        })
    
    # Calculate averages
    average_grade = round(sum(grade_values) / len(grade_values), 2)
    average_unweighted_gpa = round(total_unweighted_gpa / len(grade_values), 2)
    average_weighted_gpa = round(total_weighted_gpa / len(grade_values), 2)
    
    # Return the formatted output and detailed results as a JSON response
    return jsonify({
        'output': formatted_output,
        'detailedResults': detailed_results,
        'averageGrade': average_grade,
        'averageUnweightedGPA': average_unweighted_gpa,
        'averageWeightedGPA': average_weighted_gpa
    })

if __name__ == '__main__':
    app.run(port=8080, debug=True, host='0.0.0.0')
