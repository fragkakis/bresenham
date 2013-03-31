package org.fragkakis;

import java.util.ArrayList;
import java.util.List;

/**
 * Implementation of the Bresenham line algorithm.
 * @author fragkakis
 *
 */
public class Bresenham {
	
	/**
	 * Returns the list of array elements that comprise the line. 
	 * @param grid the 2d array
	 * @param x0 the starting point x
	 * @param y0 the starting point y
	 * @param x1 the finishing point x
	 * @param y1 the finishing point y
	 * @return the line as a list of array elements
	 */
	public static <T> List<T> findLine(T[][] grid, int x0, int y0, int x1, int y1) {
		
		List<T> line = new ArrayList<T>();
		
		int dx = Math.abs(x1 - x0);
		int dy = Math.abs(y1 - y0);
		
		int sx = x0 < x1 ? 1 : -1; 
		int sy = y0 < y1 ? 1 : -1; 
		
		int err = dx-dy;
		int e2;
		int currentX = x0;
		int currentY = y0;
		
		while(true) {
			line.add(grid[currentX][currentY]);
			
			if(currentX == x1 && currentY == y1) {
				break;
			}
			
			e2 = 2*err;
			if(e2 > -1 * dy) {
				err = err - dy;
				currentX = currentX + sx;
			}
			
			if(e2 < dx) {
				err = err + dx;
				currentY = currentY + sy;
			}
		}
				
		return line;
	}
	
}
