// Obtenemos el canvas y el contexto
const canvas = document.getElementById('canvas');
const context = canvas.getContext('2d');

// Tamaño del canvas y de la matriz
const canvasSize = 400;
const matrixSize = 400;

// Variable para almacenar el estado de cada píxel
let matriz = [];

// Inicializamos la matriz con ceros
for (let y = 0; y < matrixSize; y++) {
    matriz[y] = [];

    for (let x = 0; x < matrixSize; x++) {
        matriz[y][x] = 0;
    }
}

// Variable para determinar si se está pintando
let isDrawing = false;

// Evento de inicio de dibujo
canvas.addEventListener('mousedown', (event) => {
    isDrawing = true;
    pintarPixel(event);
});

// Evento de dibujo
canvas.addEventListener('mousemove', (event) => {
    if (isDrawing) {
        pintarPixel(event);
    }
});

// Evento de finalización de dibujo
canvas.addEventListener('mouseup', () => {
    isDrawing = false;
});

// Función para pintar un área en el canvas
function pintarPixel(event) {
    const x = Math.floor(event.clientX - canvas.offsetLeft);
    const y = Math.floor(event.clientY - canvas.offsetTop);

    context.fillStyle = 'black';
    context.fillRect(x, y, 17, 17);

    const matrizX = Math.floor(x * (matrixSize / canvasSize));
    const matrizY = Math.floor(y * (matrixSize / canvasSize));

    // Actualizar los píxeles adyacentes en la matriz
    for (let i = matrizY - 8; i <= matrizY + 8; i++) {
        for (let j = matrizX - 8; j <= matrizX + 8; j++) {
            if (i >= 0 && i < matrixSize && j >= 0 && j < matrixSize) {
                matriz[i][j] = 1;
            }
        }
    }
}

function downscale(matriz, newWidth, newHeight) {
  const width = matriz[0].length;
  const height = matriz.length;

  const scaleX = width / newWidth;
  const scaleY = height / newHeight;

  const nuevaMatriz = [];

  for (let y = 0; y < newHeight; y++) {
    const newRow = [];
    for (let x = 0; x < newWidth; x++) {
      const offsetX = Math.floor(x * scaleX);
      const offsetY = Math.floor(y * scaleY);

      let sum = 0;
      for (let j = 0; j < scaleY; j++) {
        for (let i = 0; i < scaleX; i++) {
          sum += matriz[offsetY + j][offsetX + i];
        }
      }

      var average = Math.ceil(sum / (scaleX * scaleY));
      if (average >= 1) {
        average = 1;
      }
      newRow.push(average);
    }
    nuevaMatriz.push(newRow);
  }

  return nuevaMatriz;
}

// Función para convertir el canvas a una matriz de 0 y 1
function convertirAMatriz() {
    console.log(matriz);

    const matrizReducida = downscale(matriz, 28, 28);
    console.log(matrizReducida);
    console.log(JSON.stringify(matrizReducida));

    fetch('/backpropagation', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({'matriz': matrizReducida})
    })
    .then(response => response.json())
    .then(data => {
        console.log(data);
        const answer = data.answer;
        console.log(answer);
        document.getElementById("popup-title").textContent = "Backpropagation!"
        document.getElementById("popup-content").textContent = "Your number is " + answer + "!";
    })
    .catch(error => {
        console.error('Error:', error);
        document.getElementById("popup-title").textContent = "ERROR!"
        document.getElementById("popup-content").textContent = "We're so sorry, MNIST++ is not working very well today :(";
    });

}


// Función para limpiar el contenido del canvas y la matriz
function limpiarCanvas() {
    context.clearRect(0, 0, canvas.width, canvas.height);

    for (let y = 0; y < matrixSize; y++) {
        for (let x = 0; x < matrixSize; x++) {
            matriz[y][x] = 0;
        }
    }
}
