docker:
	docker build -t smart-mirror/graphics-service .

run:
	xhost +
	docker run --rm -i -t \
	 -v $(PWD):/usr/smart-mirror \
	 -v /tmp/.X11-unix:/tmp/.X11-unix \
	 -w /usr/smart-mirror \
	 -e DISPLAY=host.docker.internal:0.0 \
	 -e LIBGL_ALWAYS_INDIRECT=1 \
	 smart-mirror/graphics-service
	xhost -

raylib:
	mkdir build
	cd build && cmake ..
	cd build && cmake --build .

clean:
	rm -r -f build