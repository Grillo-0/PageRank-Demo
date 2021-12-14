# PageRank-Demo
![image](https://github.com/Grillo-0/PageRank-Demo/blob/media/graph.svg)

A PageRank demonstration for a Linear Algebra presentation

## Prerequisites
- [Armadillo](http://arma.sourceforge.net/) Linear Algebra Library
- [graphviz](https://graphviz.org/)

## How to run

Compile it by

```bash
make page-rank
```

Then create an image with 100 nodes wth a max of 3 edges per node and a p of 0.15

```bash
page-rank 100 3 0.15 | neato -Tsvg -o file.svg
```
