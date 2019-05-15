## C++ Aquatic Simulation

This program deals with a simple agent-based model of an aquatic system, idealized as a three dimensional cubic grid of with L= 5 points in each direction and periodic boundary conditions. Consider three species of
fish:
* 'minnows', which move to nearest neighboring sites, chosen with equal probability.
* 'tuna', which move to planar diagonal sites, chosen with equal probability.
* 'sharks', which move two sites along an axis and one site in a perpendicular direction. This is similar to the 'L' manner in which knights move on a chessboard, but in three dimensions.  Choose one of these possible 'L' moves with equal probability.

After a fish moves, there are several possible outcomes depending on what is located at the arrival site:
* If the arrival site contains at least two minnows, three additional minnows are produced.
* If the arrival site contains at least two tuna who have eaten since being born, an additional tuna is produced.
* If the arrival site contains at least two sharks who have eaten since being born, an additional shark is produced.
* If the arrival site contains a tuna and any number of minnows, delete all minnows at the arrival site.
* If the arrival site contains at least one tuna and at least one shark, delete a tuna at the arrival site.
* Feeding frenzy: if the arrival site contains a shark, delete all minnows at the arrival site and at any neighboring sites.
Note that based on the occupancy of the arrival site, multiple outcomes are possible. If this is the case, choose one of the possible outcomes with equal probability.  Additionally, (before the outcome is chosen) if any shark or tuna moves 5 times without eating, it dies and must be deleted.

The system evolves by first choosing a species of fish at random from all extant species. Then a single fish
from that species is chosen at random and moves with probability p = 0.9. A series of L<sup>3</sup> such updates (and the corresponding outcomes discussed above) constitute a ‘sweep’ of the system. Determine a set of initial conditions for (N<sub>shark</sub>, N<sub>tuna</sub>, N<sub>minnow</sub>) such that each of the three species has a non-zero population after 1000 sweeps.
