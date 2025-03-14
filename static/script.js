// Theme toggle functionality
const themeToggle = document.getElementById('theme-toggle');
const themeIcon = document.querySelector('.theme-icon');

// Check for saved theme preference or default to light
const savedTheme = localStorage.getItem('theme') || 'light';
document.documentElement.setAttribute('data-theme', savedTheme);
updateThemeIcon(savedTheme);

// Toggle theme function
themeToggle.addEventListener('click', () => {
  const currentTheme = document.documentElement.getAttribute('data-theme');
  const newTheme = currentTheme === 'light' ? 'dark' : 'light';
  
  document.documentElement.setAttribute('data-theme', newTheme);
  localStorage.setItem('theme', newTheme);
  updateThemeIcon(newTheme);
});

function updateThemeIcon(theme) {
  themeIcon.textContent = theme === 'light' ? '🌙' : '☀️';
}

// Grade management
const gradeInput = document.getElementById('grade');
const addGradeButton = document.getElementById('addGrade');
const gradesList = document.getElementById('gradesList');
const calculateButton = document.getElementById('calculateGPA');

let grades = [];

// Add a new grade to the list
addGradeButton.addEventListener('click', () => {
  const gradeValue = parseFloat(gradeInput.value);
  if (isNaN(gradeValue) || gradeValue < 0 || gradeValue > 115) {
    alert('Please enter a valid grade between 0 and 115');
    return;
  }
  
  const selectedLevel = document.querySelector('input[name="courseLevel"]:checked').value;
  const levelLabel = selectedLevel === 'none' ? 'Regular' : 
                    selectedLevel === 'honors' ? 'Honors' : 'IB/DE';
  
  // Add to our data array
  grades.push({
    grade: gradeValue,
    level: selectedLevel
  });
  
  // Create list item
  const li = document.createElement('li');
  li.className = 'grade-item';
  li.dataset.index = grades.length - 1;
  
  li.innerHTML = `
    <div class="grade-info">${gradeValue} (${levelLabel})</div>
    <button class="btn-delete">✕</button>
  `;
  
  // Add delete functionality
  const deleteButton = li.querySelector('.btn-delete');
  deleteButton.addEventListener('click', () => {
    const index = parseInt(li.dataset.index);
    grades.splice(index, 1);
    updateGradesList();
  });
  
  gradesList.appendChild(li);
  
  // Reset input
  gradeInput.value = '';
  document.getElementById('levelNone').checked = true;
});

// Update the displayed list
function updateGradesList() {
  gradesList.innerHTML = '';
  grades.forEach((grade, index) => {
    const levelLabel = grade.level === 'none' ? 'Regular' : 
                      grade.level === 'honors' ? 'Honors' : 'IB/DE';
    
    const li = document.createElement('li');
    li.className = 'grade-item';
    li.dataset.index = index;
    
    li.innerHTML = `
      <div class="grade-info">${grade.grade} (${levelLabel})</div>
      <button class="btn-delete">✕</button>
    `;
    
    const deleteButton = li.querySelector('.btn-delete');
    deleteButton.addEventListener('click', () => {
      grades.splice(index, 1);
      updateGradesList();
    });
    
    gradesList.appendChild(li);
  });
}

// ==== MODIFIED POST REQUEST FUNCTIONALITY TO INCLUDE WEIGHTS ====
calculateButton.addEventListener('click', function() {
   if (grades.length === 0) {
     alert('Please add at least one grade');
     return;
   }
   
   // Convert grades array to comma-separated strings
   const gradesString = grades.map(g => g.grade).join(', ');
   const weightsString = grades.map(g => {
     if (g.level === 'none') return '0';
     else if (g.level === 'honors') return '0.5';
     else return '1.0'; // ibde
   }).join(', ');
   
   fetch('/submit', {  
      method: 'POST',  
      headers: {  
         'Content-Type': 'application/x-www-form-urlencoded',  
      },  
      body: `grades=${gradesString}&weights=${weightsString}`  
   })  
   .then(response => response.json())  
   .then(data => {  
      const resultDiv = document.getElementById('result');  
      if (data.error) {  
         resultDiv.innerHTML = `<p style="color:red;">${data.error}</p>`;  
      } else {
         // Create a more formatted display of results
         let resultsHTML = `<h2>Results:</h2>`;
         
         if (data.detailedResults) {
           resultsHTML += `<div class="result-details">`;
           data.detailedResults.forEach((item, index) => {
             resultsHTML += `
               <div class="grade-result">
                 <strong>Grade ${index+1}:</strong> ${item.grade}% (${item.letter})
                 <br>Unweighted GPA: ${item.unweightedGPA}
                 <br>Weighted GPA: ${item.weightedGPA}
               </div>
             `;
           });
           resultsHTML += `</div>`;
           
           resultsHTML += `
             <div class="result-summary">
               <h3>Summary:</h3>
               <p><strong>Average Grade:</strong> ${data.averageGrade}%</p>
               <p><strong>Unweighted GPA:</strong> ${data.averageUnweightedGPA}</p>
               <p><strong>Weighted GPA:</strong> ${data.averageWeightedGPA}</p>
             </div>
           `;
         } else {
           resultsHTML += `<p>${data.output}</p>`;
         }
         
         resultDiv.innerHTML = resultsHTML;
      }  
   });  
});  

// Add sample grade for demonstration
setTimeout(() => {
  gradeInput.value = (Math.random() * 101).toFixed(2);
}, 500);
// ============ END ORIGINAL POST FUNCTIONALITY ============
