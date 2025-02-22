from flask import Flask, render_template
app = Flask(__name__)

@app.route('/')
def home():
    return render_template('web.html') # Make sure index.html is in the 'templates' folder

@app.route('/features')
def about():
    return render_template('about.html') # Another page, for example

@app.route('/info')
def contact():
    return render_template('info.html') # Contact page, another HTML template

if __name__ == '__main__':
   app.run(debug=True)
