# Windows Installation

```docker build -t smart-mirror/api-service .```

```docker run --rm -i -t -v %cd%:/app -w /app -p 0.0.0.0:7000:7000 smart-mirror/api-service```

```python3 -m api```

# Mac/Linux Installation
```docker build -t smart-mirror/api-service .```

```docker run --rm -i -t -v ${PWD}:/app -w /app -p 0.0.0.0:7000:7000 smart-mirror/api-service```

```python3 -m api```