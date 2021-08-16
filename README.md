# RGB Led Server
Homemade smart RGB led light. You can control it from anywhere and any device that can connect to the Internet.

Connect the light to electricity or computer, wait for all the lights to turn white first and then each unit (right, middle and left) one by one and turn on red, green and blue respectively. Request the ip address of the device into your browser, now you can change the color of the lights as you wish with just one click.

![image](https://user-images.githubusercontent.com/56413673/129596102-4d8c7f92-49a7-4b85-9f0c-adef4cd39c94.png)

Also you can control it via [Wget](https://www.gnu.org/software/wget/), [cURL](https://curl.se/), etc.

### Endpoints

+ Solid colors
  + rgb color with hex color code: `GET` `/rgb/:hex-code`
    + example usage: `/rgb/ff00ff` --> magenta
  + all units red: `GET` `/color/r`
  + all units green: `GET` `/color/g`
  + all units blue: `GET` `/color/b`
+ Wavy colors
  + lineer: `GET` `/lineer/:time-level`
    + braething with lineer color changing (red -> green -> blue)
  + fade: `GET` `/fade/:time-level`
    + soft color changing (hue)
  + wave: `GET` `/wave/:time-level`
    + soft and unit based color changing

## Examples
### /color/r
![red-screenshot](https://user-images.githubusercontent.com/56413673/129603169-9012b4b4-4007-4cda-9945-c2618a9654a5.jpeg)
---

### /color/g
![green-screenshot](https://user-images.githubusercontent.com/56413673/129603203-4b24d161-408f-406e-8d73-6aad9338c45a.jpeg)
---

### /color/b
![blue-screenshot](https://user-images.githubusercontent.com/56413673/129603264-a634aa98-a3dd-4151-9f1a-303a081f3333.jpeg)
---
### /rgb/3205de
![rgb-screenshot](https://user-images.githubusercontent.com/56413673/129603323-657c81f4-2beb-4099-98c3-cebdd22ca09b.jpeg)
---

### /lineer/2
![lineer-video](https://user-images.githubusercontent.com/56413673/129601231-9769e6e9-8316-432a-84b5-45971c917612.gif)
---

### /fade/2
![fade-video](https://user-images.githubusercontent.com/56413673/129601480-841d0cb3-a2db-43c5-9215-a8da7250c0bf.gif)
---

### /wave/2
![wave-video](https://user-images.githubusercontent.com/56413673/129602016-eebbc702-ca9a-4014-a15c-c67a30039d6d.gif)
---

# For developers

## File Structure

```bash
.
├── LICENSE
├── panel.h # rgb panel controller
├── README.md
├── rgb_led.ino  # MAIN FILE
└── server.h # http server
```
