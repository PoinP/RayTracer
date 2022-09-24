# RayTracing

## Added Parallelism to the code.
### The program runs aprox. 7x faster than running it on a single core.

This has been tested on a Ryzen 5 2600 6C, 12T CPU. The test isn't scientific or anything like that. I was running other programs while rendering.

With parallel rendering the the scene below took on average 34 seconds to render.
With single thread rendering the scene below took on average 247 seconds to render.
Which is around 7 times faster.

I may be able to tweak the rendering time by changing the `blockSize`, but honestly I could not really care less. I am happy with the current boost in performance!

![Output](/FirstSteps/out/Hyper-Thread-Test.png)

The picture below is the rendering from the Raytracing in a weekend book. It took around 33 minutes to render:

![Render](/FirstSteps/out/RTWeekend.png)

    > Side note: If you need to use random numbers in a number of threads `thread_safe` is great!

Below is a sample of texture mapping on a sphere.

![Texture-Mapping](/FirstSteps/out/Texture-Mapping.png)

![Box-Render](/FirstSteps/out/RenderBox.png)

![Boxies](/FirstSteops/out/Boxies.png)