docker:
	docker build -t sahiljain11/smart-mirror .

run:
	xhost +
	docker run --rm -i -t \
	 -v $(PWD):/usr/smart-mirror \
	 -v /tmp/.X11-unix:/tmp/.X11-unix \
	 -w /usr/smart-mirror \
	 -e DISPLAY=host.docker.internal:0.0 \
	 -e LIBGL_ALWAYS_INDIRECT=1 \
	 sahiljain11/smart-mirror
	xhost -

raylib:
	mkdir build
	cd build && cmake ..
	cd build && cmake --build .

clean:
	rm -r -f build