# Picture-Frame-Tag
A fun program between two picture frames. one frame HAS to be on, but 2 cant be on at the same time. Frame A turns Frame B on and vice versa. Whos it!

Things needed
2 x ESP8266
1 x Raspberry pi running MQTT as a broker
2 x Shadow boxes that can fit whatever you are lighting up (I have the ESP8266 framed just below a photo of who is pushing the button)


The frames work by rebooting when you press the button. When the system reboots, the frame turns its own lights off and shoots a signal to Frame B to turn its lights on, and vice versa.
