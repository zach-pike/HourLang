# How do packages work?
Packages get compiled as dll files which the interpreter dynamicially loads at runtime, the module "name" is determined by the file. simply, if the file is named "math.dll", the matching import would look like this `import math;`
