# Windows Installation

In order to run raylib on Windows, please ensure that you have an Nvidia chip in your machine. If you do not, please let me know, and we can work something out.

For this setup, you will need two technologies: [X-server](https://sourceforge.net/projects/xming/) and [Docker](https://www.docker.com/). Docker, if you're unfamiliar, is a software that will allow you to run code in different OS environments. In our case, we'll be running it in a Linux container. However, our application is also a graphics application. That is where X-servers come in to play. Essentially, they allow us to stream video information to a particular port. Please install those programs before proceeding.

Once you have X-Server installed, launch it (it may be under the name "X-Launch"). After doing so, set `Display Number` to 0 and hit next. Ensure `Start no client` is selected and hit next. This next screen is VERY IMPORTANT! Please make sure to **uncheck** `Native opengl` and **check** `Disable access control`. This configuration is crucial to getting the X-Server graphics working. Then, hit next and the finish. Congrats, your X-Server should now be working in the background!

Now, we have to create our docker container. To do so, open up your terminal or command prompt and navigate to the directory where all of this code is. After doing so, run the following command (feel free to replace `sahiljain/smart-mirror` with any name of your choice):
```docker build -t sahiljain11/smart-mirror .```
or
```docker build -t <name_of_container> .```

This initial command will take a while to compute. Don't worry! It should be done in around ~10 minutes. You only need to do this once so you don't have to worry about this anymore while developing. Now, we can run our container using the following command:
```docker run --rm -i -t -v %cd%:/usr/smart-mirror -w /usr/smart-mirror -e DISPLAY=<ip_address>:0.0 <name_of_container>```

In order to get the ip address of your network, you can enter `ipconfig`, and under `Wireless LAN adapter Wi-Fi`, you can find the IPv4 address.

Once inside the docker container, run the following:
```$ make raylib```

If there's an error about caching, run the following command:
```$ cmake --build .```

Once that's done, you can do the following and a graphics screen should pop up!
```$ ./jarvis.csj```