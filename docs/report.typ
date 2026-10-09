// CS 450/550 Introduction to Computer Graphics — Project 1
// Compile with: typst compile docs/report.typ docs/report.pdf

#set page(paper: "us-letter", margin: 1in)
#set text(font: "New Computer Modern", size: 11pt, lang: "en")
#set heading(numbering: "1.")
#set par(justify: true)

#align(center)[
  #text(size: 13pt, weight: "bold")[CS 450/550 — Introduction to Computer Graphics]
  #v(0.4em)
  #text(size: 20pt, weight: "bold")[Project 1: Bounding Spheres, Trackball, and Silhouettes]
  #v(0.8em)
  #table(
    columns: (auto, 2.2in, auto, 1.8in),
    align: (left, left, left, left),
    [*Student*], [Khang Le], [*OSU ID*], [934768758],
    [*Course*], [CS 550], [*Date*], [October 9, 2026],
  )
]

#v(1em)
#block(inset: 10pt, stroke: (left: 2.5pt), radius: 2pt)[
  *Summary.* This project implements automatic model normalization using a
  bounding sphere, quaternion-based trackball rotation, and silhouette
  rendering. Because this is the CS 550 version, the report also enumerates
  the twelve rotational symmetries of the specified tetrahedron.
]

= Implementation

The implementation is contained in `src/mesh.cpp`, `src/camera.cpp`, and
`src/main.cpp`. The program is built with CMake and run with one PLY model path:

```bash
cmake --build build
./build/learnply2 models/bunny.ply
```

The controls are left-drag for trackball rotation, `1` for wireframe, `2` for
silhouette rendering, `R` for reset, and Escape to quit.

= 1. Bounding sphere

== 1(a). Computation and normalization

For vertex positions $p_1, dots, p_n$, I compute the object-space center as the
mean of all vertices:

$ c = 1/n sum_(i=1)^n p_i. $

The radius is the greatest distance from this center to a vertex:

$ r = max_(1 <= i <= n) ||p_i - c||. $

The model matrix applies the transformation

$ p'_i = (p_i - c) / r. $

Thus the center is at the origin and every vertex is inside a sphere of radius
one. This is implemented in `Mesh::compute_properties()` and applied before
the camera view matrix in `display()`.

== 1(b). Alternative bounding sphere

The center used above is convenient but is not generally the center of the
smallest enclosing sphere. A minimum-enclosing-sphere algorithm, such as
Welzl's randomized algorithm, instead solves

$ min_(c,r) r quad "subject to" ||p_i - c|| <= r " for every " i. $

The resulting radius satisfies

$ r_"minimum" <= r_"mean-center". $

This can use more pixels because the sphere center is allowed to move toward
an asymmetric group of vertices. The tradeoff is that the algorithm is more
complex than the one-pass mean-center method. Insert a diagram here comparing
the two circles for an asymmetric point set.

== 1(a) results

The required combined screenshot grids are provided in the appendix. The
upper-left panel is the original view and the upper-right panel is the
bounding-sphere-normalized view. The lower panels contain the natural normal
and silhouette views required by Parts 2(a) and 3(a).

= 2. Trackball interface

== 2(a). Trackball implementation and natural orientations

Mouse coordinates are converted to normalized coordinates and projected onto
a virtual unit sphere. Points outside the disk are placed on the equator.
For old and new projected points $p_0$ and $p_1$, the rotation axis and angle
are

$ a = (p_0 times p_1) / ||p_0 times p_1|| $ \
$ theta = arccos("clamp"(p_0 dot p_1, -1, 1)). $

The quaternion `angleAxis(theta, a)` is multiplied into the camera
orientation. The lower-right panel of each model grid shows its selected
natural orientation using normal wireframe rendering.

== 2(b)(ii). Tetrahedron rotational symmetry group

The four specified tetrahedron vertices are permuted by every rotational
symmetry. The rotation group is the even permutation group $A_4$, so it has
$|A_4| = 12$ elements. They consist of the identity, eight rotations of 120 or
240 degrees about vertex-to-opposite-face axes, and three 180-degree rotations
about opposite-edge axes.

Quaternion convention: $q=(w,x,y,z)$, with the vector part equal to
$sin(theta/2) a$ for a unit axis $a$.

#table(
  columns: (auto, auto, auto, 1fr),
  align: left,
  table.header([*Quaternion*], [*Axis*], [*Angle*], [*Matrix*]),
  [$ (1,0,0,0) $], [$-$], [0°], [$ mat(1,0,0; 0,1,0; 0,0,1) $],
  [$ (1/2,1/2,1/2,1/2) $], [$(1,1,1)$], [120°], [$ mat(0,0,1; 1,0,0; 0,1,0) $],
  [$ (-1/2,1/2,1/2,1/2) $], [$(1,1,1)$], [240°], [$ mat(0,1,0; 0,0,1; 1,0,0) $],
  [$ (1/2,1/2,-1/2,-1/2) $], [$(1,-1,-1)$], [120°], [$ mat(0,0,-1; -1,0,0; 0,1,0) $],
  [$ (-1/2,1/2,-1/2,-1/2) $], [$(1,-1,-1)$], [240°], [$ mat(0,-1,0; 0,0,1; -1,0,0) $],
  [$ (1/2,-1/2,1/2,-1/2) $], [$(-1,1,-1)$], [120°], [$ mat(0,0,1; -1,0,0; 0,-1,0) $],
  [$ (-1/2,-1/2,1/2,-1/2) $], [$(-1,1,-1)$], [240°], [$ mat(0,-1,0; 0,0,-1; 1,0,0) $],
  [$ (1/2,-1/2,-1/2,1/2) $], [$(-1,-1,1)$], [120°], [$ mat(0,0,-1; 1,0,0; 0,-1,0) $],
  [$ (-1/2,-1/2,-1/2,1/2) $], [$(-1,-1,1)$], [240°], [$ mat(0,1,0; 0,0,-1; -1,0,0) $],
  [$ (0,1,0,0) $], [$(1,0,0)$], [180°], [$ mat(1,0,0; 0,-1,0; 0,0,-1) $],
  [$ (0,0,1,0) $], [$(0,1,0)$], [180°], [$ mat(-1,0,0; 0,1,0; 0,0,-1) $],
  [$ (0,0,0,1) $], [$(0,0,1)$], [180°], [$ mat(-1,0,0; 0,-1,0; 0,0,1) $],
)

The list is complete because the identity contributes one element, each of
the four vertices gives two nonidentity 3-fold rotations, and each of the
three pairs of opposite edges gives one half-turn. Their totals are
$1+4(2)+3=12$, matching $|A_4|$.

= 3. Silhouette rendering

== 3(a). Method and results

The program first renders the triangles as a white depth-tested surface. It
then transforms each triangle normal using the inverse-transpose normal
matrix. For an edge with adjacent faces having view-space facing values
$d_i = n_i dot (0,0,1)$, the edge is drawn when

$ d_0 d_1 < 0. $

Boundary edges are also drawn. Replace the lower-left panel of every model
grid with the corresponding silhouette result.

== 3(b). Discussion and improvements

The technique clearly emphasizes the outer contour, but line quality can be
affected by mesh tessellation, aliasing, and inconsistent normals. Two
potential improvements are:

+ Use anti-aliased, view-dependent line width so thin and thick regions remain
  visually consistent.
+ Improve treatment of boundary edges and sharp creases, possibly by using a
  crease-angle threshold and a dedicated outline pass.

Insert close-up images here showing the specific artifacts observed in the
rendered models.

= Conclusion

The completed viewer normalizes arbitrary meshes, supports interactive
quaternion trackball rotation, and extracts silhouette edges from adjacent
face orientations. The tetrahedron analysis independently confirms the twelve
rotational symmetries required for the CS 550 portion of the assignment.

= Appendix: Combined screenshot grids

For each model, replace the four labeled boxes with one final 2-by-2 screenshot
grid. The order must be: original, bounding-sphere adjusted, silhouette in the
natural orientation, and normal rendering in the natural orientation.

#let screenshot-placeholder(model) = figure(
  grid(
    columns: 2,
    gutter: 3pt,
    rect(width: 100%, height: 0.63in, fill: luma(245), stroke: gray)[
      #align(center + horizon)[Original]
    ],
    rect(width: 100%, height: 0.63in, fill: luma(235), stroke: gray)[
      #align(center + horizon)[Bounding sphere]
    ],
    rect(width: 100%, height: 0.63in, fill: luma(225), stroke: gray)[
      #align(center + horizon)[Silhouette]
    ],
    rect(width: 100%, height: 0.63in, fill: luma(215), stroke: gray)[
      #align(center + horizon)[Natural normal]
    ],
  ),
  caption: [#text(weight: "bold")[#model + ".ply"]]
)

#grid(
  columns: 2,
  gutter: 12pt,
  screenshot-placeholder("bunny"),
  screenshot-placeholder("dragon"),
  screenshot-placeholder("torus"),
  screenshot-placeholder("dodecahedron"),
  screenshot-placeholder("cube"),
  screenshot-placeholder("feline"),
  screenshot-placeholder("sphere"),
  screenshot-placeholder("happy"),
  screenshot-placeholder("icosahedron"),
  screenshot-placeholder("octahedron"),
  screenshot-placeholder("tetrahedron"),
  screenshot-placeholder("eight"),
)
