from flask import (
    Flask,
    jsonify,
    render_template,
    request
)
import os
import subprocess
import struct

carpeta_actual = os.getcwd()
carpeta_static = carpeta_actual + "/templates/static"

app = Flask(__name__, static_folder=carpeta_static)


@app.route('/')
def index():
    return render_template('index.html')


@app.route("/backpropagation", methods=['POST'])
def backpropagation():
    matrix = request.get_json()['matriz']
    with open('matrix.bin', 'wb') as file:
        rows = len(matrix)
        columns = len(matrix[0])
        file.write(struct.pack('ii', rows, columns))
        for f in matrix:
            for element in f:
                file.write(struct.pack('i', element))
    result = subprocess.run(
        ["./cmake-build-debug/inference"],
        text=True,
        capture_output=True
    )
    response = {"answer": result.stdout}
    return jsonify(response)


if __name__ == '__main__':
    app.run(debug=True, port=5000)
