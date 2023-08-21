import requests
import numpy as np
import cv2


url = 'http://127.0.0.1:8000/predict'
webcam = cv2.VideoCapture(0)

while True:
    result, frame = webcam.read()

    if result is False:
        break

    cv2.imwrite('image.jpg', frame)

    with open('image.jpg', 'rb') as file:
        response = requests.post(url, files={'file': file})

    if response.ok:
        file_bytes = np.asarray(bytearray(response.content), dtype=np.uint8)

        # Decode the numpy array as an image
        image = cv2.imdecode(file_bytes, cv2.IMREAD_COLOR)

        cv2.imshow('prediction', image)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    else:
        print("Something went wrong!")
        break


webcam.release()
cv2.destroyAllWindows()

