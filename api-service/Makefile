docker:
	docker build -t smart-mirror/api-service .

run:
	docker run --rm -i -t \
	 -v $(PWD):/app \
	 -w /app \
	 -p 0.0.0.0:7000:7000 \
	 smart-mirror/api-service

clean:
	rm -r -f build