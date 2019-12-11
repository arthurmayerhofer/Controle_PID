import cv2
import numpy as np

elementoEstruturante = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5))

pote = cv2.imread('plantaozao.jpeg')
planta = cv2.imread('plantaozao.jpeg')
plantinha = cv2.imread('plant.jpeg')
#pote = cv2.resize(pote,None,fx=0.2,fy=0.2)
#planta = cv2.resize(planta,None,fx=0.2,fy=0.2)

lower_green = np.array([18, 94, 140])
upper_green = np.array([48, 255, 255])

lower_red = np.array([0,120,70])
upper_red = np.array([10,255,255])

pote = cv2.GaussianBlur(pote, (5, 5), 0)
planta = cv2.GaussianBlur(planta, (5, 5), 0)


hsvPote = cv2.cvtColor(pote, cv2.COLOR_BGR2HSV)
hsvPlanta = cv2.cvtColor(planta, cv2.COLOR_BGR2HSV)
maskPote = cv2.inRange(hsvPote, lower_red, upper_red)
maskPlanta = cv2.inRange(hsvPlanta, lower_green, upper_green)


dilatePlanta = cv2.dilate(maskPlanta, elementoEstruturante, iterations = 1)

_, contoursPote,hierarchyPote = cv2.findContours(maskPote,  cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
_,contoursPlanta,hierarchyPlanta = cv2.findContours(dilatePlanta, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)


cv2.drawContours(plantinha, contoursPlanta, -1, (0,0,255), 2)
cv2.drawContours(plantinha, contoursPote, -1, (0,255,0), 2)

cntPlanta = contoursPote[0]
cntPote = contoursPlanta[0]


soma_area_pote = 0
for i in range(len(contoursPote)):
	soma_area_pote += cv2.contourArea(contoursPote[i])


soma_area_planta = 0
for i in range(len(contoursPlanta)):
	soma_area_planta += cv2.contourArea(contoursPlanta[i])



areaPlantaReal = (243 * soma_area_planta) / soma_area_pote
print("Area Real Planta: " + str(areaPlantaReal) + " cm2")


areaPote = cv2.contourArea(cntPote)
areaPlanta = cv2.contourArea(cntPlanta)

font = cv2.FONT_HERSHEY_SIMPLEX
cv2.putText(plantinha, "areaReal: " + str(areaPlantaReal) + " cm2" ,(0,1900), font, 5 ,(0,0,0 ),10,cv2.LINE_AA)
cv2.imshow("pranta", plantinha)
cv2.imwrite("pranta.jpeg", plantinha)

cv2.waitKey(0)
cv2.destroyAllWindows()