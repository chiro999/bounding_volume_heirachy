import numpy as np
from pynavlib import bvh_tree, bounding_box, sphere, ray, triangle, box, intersection

# Define some geometric primitives (triangles and boxes) for the BVH nodes.
vertices1 = np.array([[0, 0, 0], [1, 0, 0], [0, 1, 0]])
triangle1 = triangle(vertices=vertices1)
bbox1 = bounding_box([sphere(center=[0.5, 0.5, -0.5], radius=np.sqrt(2)/2)])

# Create another triangle positioned behind the first one for better visualization of hidden objects in BVH traversal
vertices2 = np.array([[0, 0, -1], [1, 0, -1], [0, 1, -1]])
triangle2 = triangle(vertices=vertices2)
bbox2 = bounding_box([sphere(center=[0.5, 0.5, -1.5], radius=np.sqrt(2)/2)])

# Initialize an empty BVH tree and add nodes (bounding boxes) to it.
bvh = bvh_tree()
bvh.add_node(bbox1, data={"triangle": triangle1})
bvh.add_node(bbox2, data={"triangle": triangle2})  # This node is "behind" the first one due to its z-position

# Define a ray for intersection testing.
ray_origin = np.array([0, 0, -3])
ray_direction = np.array([0, 0, 1])
test_ray = ray(origin=ray_origin, direction=ray_direction)

# Perform the traversal and check for intersections with the BVH tree.
intersections = bvh.traverse(test_ray, intersect_func=intersection)
if len(intersections) > 0:
    print("Intersection found!")
else:
    print("No intersection.")
