import cv2 as cv
import numpy as np 
import serial

ser = serial.Serial('COM9',9600)

cap = cv.VideoCapture(0)
def nothing(x):
    pass
cv.namedWindow("TRACKING")
cv.createTrackbar("LH","TRACKING",0,255, nothing)
cv.createTrackbar("LS","TRACKING",0,255, nothing)
cv.createTrackbar("LV","TRACKING",0,255,nothing)
cv.createTrackbar("UH","TRACKING",255,255,nothing)
cv.createTrackbar("US","TRACKING",255,255,nothing)
cv.createTrackbar("UV","TRACKING",255,255,nothing)


while True :
    ret , frame = cap.read()
    cv.imshow('frame',frame)
    canny = cv.Canny(frame,125,175)
    resized=cv.resize(frame,(300,250),interpolation=cv.INTER_CUBIC)
    #ok = cv.cvtColor(frame,cv.COLOR_BGR2HSV)
    #cv.imshow('ok',ok)
    lh=cv.getTrackbarPos("LH","TRACKING")
    ls=cv.getTrackbarPos("LS","TRACKING")
    lv=cv.getTrackbarPos("LV","TRACKING")
    uh=cv.getTrackbarPos("UH","TRACKING")
    us=cv.getTrackbarPos("US","TRACKING")
    uv=cv.getTrackbarPos("UV","TRACKING")
    x12=0
    y12=0
    x1=0
    y1=0
    #lower=np.array([lh,ls,lv])
    #upper=np.array([uh,us,uv])
    
    lower=np.array([75,24,9])
    upper=np.array([255,66,57])

    mask=cv.inRange(frame,lower,upper)
    result=cv.bitwise_and(frame,frame,mask=mask)

    contours,_ = cv.findContours(mask,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
    for cnt in contours : 
    #calculate area and remove small elements
          
          area = cv.contourArea(cnt)
         
              
          if area > 200 :

               
               ser.write(str.encode('1'))
               

               #cv.drawContours(img,[cnt],-1,(0,225,0),2)
               x,y,w,h = cv.boundingRect(cnt)
               cv.rectangle(result,(x,y),(x + w,y + h),(0,255,0),1)
               x1=int((x + x+w)/2)
              
               y1=int((y +y+h)/2)
               
               
               

    lower1=np.array([19,19,54])
    upper1=np.array([50,38,138])

    mask1=cv.inRange(frame,lower1,upper1)
    result1=cv.bitwise_and(frame,frame,mask=mask1)
    contours1,_ = cv.findContours(mask1,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)

    for cnt in contours1 : 
    #calculate area and remove small elements 
          
          area = cv.contourArea(cnt)
       

          if area > 200 :
              
               ser.write(str.encode('2'))
               

               #cv.drawContours(img,[cnt],-1,(0,225,0),2)
               x,y,w,h = cv.boundingRect(cnt)
               cv.rectangle(result1,(x,y),(x + w,y + h),(0,255,0),1)
               x12=int((x + x+w)/2)
               y12=int((y +y+h)/2)
              
          
                           




    
    ser.write(str.encode('3'))     
    ser.write(str.encode('0'))
    print(x1,y1,"---",x12,y12)


    cv.imshow('frame2',result1)
    cv.imshow('frame',result)
    cv.imshow('image',frame)
    #cv.imshow('mask',mask)

    
    if cv.waitKey(1) == ord('q'):
        break 


cap.release()
cv.destroyAllWindows()





