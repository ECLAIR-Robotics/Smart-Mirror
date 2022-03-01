docker:
	docker build -t sahiljain11/smart-mirror .

run:
	xhost +
	docker run --rm -i -t \
	 -v $(PWD):/usr/smart-mirror \
	 -v /tmp/.X11-unix:/tmp/.X11-unix \
	 -w /usr/smart-mirror \
	 -e DISPLAY=${DISPLAY} \
	 -e LIBGL_ALWAYS_INDIRECT=1 \
	 sahiljain11/smart-mirror
	xhost -

# Windows:
# docker run --rm -i -t -v %cd%:/usr/smart-mirror -w /usr/smart-mirror -e DISPLAY=0.0 sahiljain11/smart-mirror

raylib:
	mkdir build
	cd build && cmake ..
	cmake --build .

clean:
	rm -r -f build