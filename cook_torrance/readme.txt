		Dynamic Cook and Torrance Lighting

Created by:  Eric Duhon
Address:     3947 Arlington sq. #319
	     Houston, TX 77034
Telephone:   (713) 947-0668
Email:	     duhone@ev1.net

Contents
	1. Installation
	2. Basic theory of effect
	3. Effect options described
	4. Mathematical Theory for effect
	5. References

1. Installation
	Unzip the zip file to the effects directory of your installation of neffectsbrowser.
	(i.e. c:\neffectsbrowser\effects\). Make sure your unzip program is set up to recreate
	Directories so that the sub folder for this particular effect (\cook torrance) is 
	Created. All project files and dll's will be unzipped to the subdirectory \cook Torrance
	under whatever you directory you pick to install it to.

2. Basic theory of effect
		My primary goal for this effect was the accurate rendering of metallic surfaces.
	The Cook and Torrance lighting model was designed for just such a purpose. 
		All of the real-time hardware implementations I have come across for bdrf 
	lighting models all seem to rely on some form of pre-computation. This has many 
	draw backs, namely the accuracy of pre-computation is limited by the size of the 
	lut you create, and a different lut texture has to be generated for every type of 
	material you wish to have in your program. However there is no question that these
	techniques are very fast.
		Vertex shaders, however, allow for enough computational power that the cook
	and Torrance lighting model could be calculated real-time. This allows the programmer
	to change the material by just changing a few numbers in constant registers. The 
	accuracy of the shader is not nearly as limited as a lut. Only the precision of the
   	shader registers limits accuracy. There is no need with this shader to pre-calculate 
	anything. The first part of my effect is this dynamic cook and Torrance vertex shader. 
		The second problem with most attempts at rendering metals is secondary reflections.
	Usually an ambient term is added to the lighting model to approximate secondary reflections.
	However, while an ambient term works fairly well for diffuse secondary reflections it can
	not accurately represent specular secondary reflections. Adding a cubemap to represent
	specular secondary reflections to an ambient term to represent diffuse secondary
	reflections provide a fairly good approximation. However this approach tends to give
	to much of a mirror appearance to the material.
		For this effect I used a variation of the basic cubemap. The cubemap is treated 
	as a light source and then inputted into the Torrance and cook lighting model to come up
	with a final value for the specular secondary reflection. This gives the cubemap more
	of the color of the material at high angles of incidence and more of the color of the 
	light source (cubemap) at low angles of incidence. This method also works extremely well for
	dull materials. For dull materials, when looking at them straight on, the
	cubemap is barely visible, but at low angles of incidence the cubemap becomes more visible.
	A good example of this type of behavior in the real world is semi-polished floors. If you 
	look straight down at them you will not see much of a reflection, it is only when looking
	further away from you that you begin to see reflections in the floor. Traditional cubemaps
	don't exhibit this behavior. The Torrance and Cook cubemap makes up the second part of my
	effect.
		The effect contains both a phong implementation and the Torrance and Cook implementations
	For comparison. You can also compare the primary lighting models and secondary (i.e. cubemap)
	lighting models separately.

3. Effect options described
		The first group of options allows you to select the lighting model you wish to use. 
	It defaults to Torrance and Cook lighting plus Torrance and Cook cubemap, which is the complete
	shader. The other lighting models are for comparison. They are described below.

	Phong Lighting:
		primary diffuse light: Standard phong diffuse Lighting
		primary specular light: Standard phong specular lighting
		secondary diffuse light: Standard phong ambient term
		secondary specular light: none

	Torrance and Cook Lgihting:
		primary diffuse light: Standard phong diffuse Lighting
		primary specular light: Torrance and Cook specular lighting
		secondary diffuse light: Standard phong ambient term
		secondary specular light: none

	Phong Cubemap:
		primary diffuse light: none
		primary specular light: none
		secondary diffuse light: none
		secondary specular light: standard cubemap

	Torrance and Cook Cubemap:
		primary diffuse light: none
		primary specular light: none
		secondary diffuse light: none
		secondary specular light: Torrance and Cook cubemap

	Phong Lgihting:
		primary diffuse light: Standard phong diffuse Lighting
		primary specular light: Standard phong specular lighting
		secondary diffuse light: Standard phong ambient term
		secondary specular light: standard cubemap

	Torrance and Cook Lighting:
		primary diffuse light: Standard phong diffuse Lighting
		primary specular light: Torrance and Cook specular lighting
		secondary diffuse light: Standard phong ambient term
		secondary specular light: Torrance and Cook cubemap

	The second set of options is used for choosing the type of material you wish to view
		Shiny Gold (default): This represents highly polished gold
		Dull Gold: This represents a duller gold than the previous
		Dull blue material: This represents no particular material it is used to view the shaders
			effectiveness at rendering dull materials.
		Silver: Just another cool shiny material to look at.
		Mirror: An example of a mirror surface rendered using the shader.

	The third set of options allows you to control the brightness of the 2 lights. There meanings
		are self explanatory.

	The fourth option is to pause the motions of the 2 lights around the teapot.


4. Mathematical Theory for effect
	Below are the mathematical formulas used in the shader. dot means the 3 component dot product 
		of 2 vectors.

	Standard Phong ambient term:
		A = Ka * Dc   where
		A = final color
		Ka = amount of secondary diffuse light (ie from material properties)
		Dc = Diffuse color of material

	Standard Phong Diffuse Lighting:
		D = Il * (Kd * (N dot L) * Dc)    where
		D = final color
		Il = light intensity
		Kd = amount of primary diffuse light
		DC = diffuse color
		N = normal vector
		L = Light vector
	
	Standard Phong Specular Lighting:
		S = Il * (Ks * (N dot H)^n)     where
		S = final color
		Il = Light intensity
		Ks = amount of primary specular light
		N = Normal Vector
		H = Halfway Vector
		n = Specular power
		
	Standard Cubemap:
		Start with previous phong specular equation S = Ks * (N dot H)^n
			since the light vector is just the view vector reflected around the normal 
			vector in a cube map, the halfway vector by definition is equal to the normal
			vector in a cube map so the equation reduces to:
		S = Ks * Il     where
		S = final color
		Ks = amount of secondary specular light
		Il = Light intensity and color sampled from the cubemap

	Cook and Torrance lighting
		The original Cook and Torrance equation is, except for F which is from Schlick
		S = dw * Ks * ((F * D * G)/(pi * (N dot V))    where
		D = 1/(4 * m^2 * (N dot H)^4) * e^(-((tan(arccos(N dot H))^2) / m^2))
		G = min(1,Gm,Gs)
		Gm = (2 * (N dot H) * (N dot V)) / (V dot H)
		Gs = (2 * (N dot H) * (N dot L)) / (V dot H)
		F = F0 + (1-(N dot V)) * (1 - F0)	from Schlick
		
		this is not very practical so its best to rearrange and simplify the equation so it works better with 
			vertex shaders. All transcendentals have been removed exept the exponent in the equation below.

		S = (B * F * D * G) / (N dot V)
		B = (dw * ks) / (2 * m^2 * pi)		can be calculated on a per object basis
		D = (e^((1/m^2) * (1-(1/(N dot H)^2))) / (N dot H)^4
		G = min(0.5,Gm,Gs)
		Gm = ((N dot H) * (N dot V)) / (V dot H)
		Gs = ((N dot H) * (N dot L)) / (V dot H)
		F = F0 + (1-(N dot V))^5 * (1 - F0)	from Schlick
		N = Normal Vector
		H = Halfway Vector
		V = View vector
		L = Light vector
		m = Reflectivity
		dw = .0001
		Ks = amount of primary specular light
		F0 = fresnel coefficient at 0 degrees angle of incidence
		
	Cook and Torrance Cubemap:
		Start with previous Cook and Torrance specular equation
			since the light vector is just the view vector reflected around the normal 
			vector in a cube map, the halfway vector by definition is equal to the normal
			vector in a cube map and N dot V is equal to N dot L so the equation reduces to:
		
		S = (B * F) / (N dot V)
		B = (dw * ks) / (4 * m^2 * pi)		can be calculated on a per object basis
		F = F0 + (1-(N dot V))^5 * (1 - F0)	from Schlick
		N = Normal Vector
		V = View vector
		m = Reflectivity
		dw = .0001
		Ks = amount of secondary specular light
		F0 = fresnel coefficient at 0 degrees angle of incidence

5. References

	Phong B. (1975) Illumination for computer-generated pictures. COMM. ACM, 18 (6), 311-17
	Cook R.L. and Torrance K. E. (1982). A reflectance model for computer graphics.  COMPUTER GRAPHICS, 15 (3), 307-16
	Watt A. (2000) 3D Computer Graphics.


