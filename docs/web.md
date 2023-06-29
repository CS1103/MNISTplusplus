# MNIST++ Website Documentation

The MNIST++ website is a simple web application that allows users to draw a number (0-9) on a canvas and perform backpropagation using a trained neural network model to predict the drawn number. This documentation provides an overview of the website's structure and functionality.

By combining the power of C++ for neural network operations and the simplicity of web development with Flask, the MNIST++ website provides a user-friendly interface for drawing and predicting handwritten digits. Users can experience the accuracy and efficiency of the MNIST++ model directly from their web browsers.

## Project Structure

The project consists of the following files:

- `main.py`: The main Python file that defines the Flask application and routes.
- `index.html`: The HTML template file that defines the structure of the website.
- `script.js`: The JavaScript file that handles canvas drawing and interaction with the Flask API.
- `style.css`: The CSS file that defines the styles and layout of the website.

## Flask Application

The Flask application is defined in `main.py`. It uses the Flask framework to handle HTTP requests and serves the website's HTML templates and static files. The main features of the Flask application are as follows:

- Importing necessary modules and setting up the Flask application.
- Defining route handlers for the root path ('/') and the '/backpropagation' path.
- The `index()` function renders the `index.html` template when the root path is accessed.
- The `backpropagation()` function handles the POST request to '/backpropagation' and performs backpropagation on the drawn number.
- The `serialize()` and `deserialize()` functions handle serialization and deserialization of the neural network model.
- Running the Flask application when the script is executed directly.

## HTML Template

The website's structure and content are defined in `index.html`. It consists of the following components:

- A header section displaying the MNIST++ logo and the website's title.
- A canvas container with a canvas element where users can draw a number.
- A button container with two buttons: "Backpropagation!" and "Clear Canvas".
- Two popup overlay sections: one for showing the loading animation and another for displaying the backpropagation result.

## JavaScript File

The `script.js` file contains the JavaScript code responsible for handling canvas drawing and interacting with the Flask API. The main features of the JavaScript code are as follows:

- Obtaining references to the canvas element and its context.
- Initializing the matrix for storing the state of each pixel.
- Handling mouse events to draw on the canvas and update the matrix.
- Implementing functions for converting the canvas to a matrix of 0s and 1s and downscaling the matrix to a smaller size.
- Sending a POST request to the '/backpropagation' route with the converted matrix when the "Backpropagation!" button is clicked.
- Displaying loading animation and handling the response from the Flask API.
- Handling the "Clear Canvas" button click event to clear the canvas and reset the matrix.

## CSS Stylesheet

The `style.css` file defines the styles and layout of the website. It includes styles for the canvas, header, buttons, overlays, and other elements.

## Tutorial: 

Once you clone the repository, you can run the MNIST++ website locally on your machine. To run the MNIST++ website, follow these steps:

1. Install the required dependencies (Flask).
```bash
    pip install -r requirements.txt
```
2. Run the command `python main.py` to start the Flask application.
3. Access the website in your browser at `http://localhost:5000`.

The website allows you to draw a number on the canvas and click the "Back propagation!" button to perform backpropagation and get the predicted number. The result will be displayed in a popup.

Note: Make sure to adjust the file paths and configurations according to your project structure.

This concludes the MNIST++ website documentation. You can now deploy and use the website to interact with the MNIST++ neural network model.

