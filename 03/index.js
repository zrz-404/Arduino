function createButtonGrid() {
    const container = document.getElementById('matrix-buttons');
    for (let index = 0; index < 64; index++) {
        const button = document.createElement('button');
        button.id = `${index}`;
        button.addEventListener('click', () => {
            if (button.classList.contains('RED')) {
                button.classList.remove('RED');
                sendColorUpdate(button.id, 'OFF');
            } else {
                button.classList.add('RED');
                sendColorUpdate(button.id, 'RED');
            }
        });
        container.appendChild(button);
    }
}

function sendColorUpdate(buttonId, color) {
    const data = new URLSearchParams();
    data.append('color', color);
    data.append('id', buttonId);
    console.log(data);
    fetch('/color', {
        method: 'POST',
        body: data
    })
    .then(response => response.text())
    .then(result => console.log(result))
    .catch(error => console.error('Error:', error));
}

function resetColors() {
    const buttons = document.querySelectorAll('.matrix-buttons button');
    buttons.forEach(button => {
        button.classList.remove('RED');
        sendColorUpdate(button.id, 'OFF');
    });
}

document.getElementById('reset-button').addEventListener('click', resetColors);


createButtonGrid();