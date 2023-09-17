# woomhuis-alarm-met-touchscreen-sd-domoticz
2 arduinos and an Nexion touchscreen 

dit huis alarm is gebaseert op 2 arduino mega's en een Nexion touchscreen.

de eerste arduino regeld het alarm voor 3 bewoners (3 verschillende pin codes) daarnaast is er nog een MASTER pincode om de pincodes aan te passen.
de pincodes en de zone's waar het alarm op is af gegaan zijn in te zien via het Nexion scherm maar ook op de cd kaart.

het alarm heeft 16 verschillende zones en 1 sabotage zone.

op iedere zone kan je meerdere bewegingssenoren en of deur contacten aan sluiten met no contacten. 
de sabotage zone moet altijd gesloten zijn, dus deze loopt van sensor naar sensor. als deze draad verbroken wordt volgt er gelijk een alarm.

er zijn 2 relais gebruikt 1 voor de flits licht (deze blijft ingeschakelt bij alarm tot deze word uitgeschakelt)
1 relais voor een sirene, deze word bij alarm automatisch uitgeschakelt na een x aantal minuten.
