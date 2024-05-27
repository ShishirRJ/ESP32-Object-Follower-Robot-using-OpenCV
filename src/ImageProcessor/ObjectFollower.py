import cv2
import numpy as np
import math
import socket
import struct

cap= cv2.VideoCapture('Enter ip address of ESP32 CAM here')
esp32_ip ='Enter ip address of ESP32 here'
esp32_port = 80 #Enter port number

#Open socket connection
esp32_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
esp32_socket.connect((esp32_ip, esp32_port))

while True:
    ret, frame= cap.read()
    cv2.resize(frame, (0,0), fx=0.1, fy=0.1)
    grey= cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blur= cv2.GaussianBlur(grey, (17,17), 0)
    circles= cv2.HoughCircles(blur, cv2.HOUGH_GRADIENT, 1.2, 1000, param1=100, param2=30, minRadius=20, maxRadius=400)
    print(circles)
    if circles is not None:
        circles=np.uint16(np.around(circles))
        for circle in circles[0, :]:
            centre= (circle[0], circle[1])
            radius= circle[2]
            cv2.circle(frame, centre, 1, (0, 255, 0), -1)
            cv2.circle(frame, centre, radius, (0,0,255), 3)
            top_corner= (int(circle[0]- radius/math.sqrt(2)), int(circle[1]- radius/math.sqrt(2)))
            bottom_corner= (int(circle[0]+ radius/math.sqrt(2)), int(circle[1]+ radius/math.sqrt(2)))
            cv2.rectangle(frame, top_corner, bottom_corner, (0, 255, 0), 3)
            frame2= frame[int(top_corner[1]): int(bottom_corner[1]), int(top_corner[0]): int(bottom_corner[0])]
            frame2_bgr = frame2  
            print(frame2)
            print(cv2.COLOR_BGR2HSV)
            if frame2.any():
                frame2_hsv = cv2.cvtColor(frame2, cv2.COLOR_BGR2HSV)  
                average_color = np.mean(frame2_hsv, axis=(0, 1))
                print("Average color (BGR):", average_color)
                print("Centre: ", centre[1])
                centre_x = centre[1]/10
                data = struct.pack('4B', int(average_color[0]), int(average_color[1]), int(average_color[2]), int(centre_x))
                if data[0]<=40 and data[0]>=20 and data[1]<=200 and data[1]>=100 and data[2]<=255 and data[2]>=135:
                    esp32_socket.sendall(data)
                else:
                    blackout = struct.pack('4B', 0, 0, 0, 0)
                    esp32_socket.sendall(blackout)

    else:
        blackout = struct.pack('4B', 0, 0, 0, 0)
        esp32_socket.sendall(blackout)


    cv2.imshow('Frame', frame)
    if cv2.waitKey(1)== ord('q') or cv2.waitKey(1)== ord('Q'):
        break

# Close the connection
esp32_socket.close()
cap.release()
cv2.destroyAllWindows()