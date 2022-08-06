docker:
	docker build -t smart-mirror/api-service .

run:
	xhost +
	docker run --rm -i -t \
	 -v $(PWD):/app \
	 -w /app \
	 -p 0.0.0.0:7000:7000 \
	 smart-mirror/api-service
	xhost -

clean:
	rm -r -f build