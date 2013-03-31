package org.fragkakis;

import java.util.List;

import org.junit.Test;

public class BresenhamTest {

	@Test
	public void test() {
		Point[][] grid = new Point[20][10];
		for(int x=0; x<grid.length; x++) {
			for(int y=0; y<grid[0].length; y++) {
				grid[x][y] = new Point(x, y);
			}
		}
		
		List<Point> line = Bresenham.findLine(grid,3, 3, 17, 7);
		
		visualize(grid, line);
	}

	/**
	 * Convenience method for visualisation.
	 * @param grid the 2d array
	 * @param line the line as a list
	 */
	private void visualize(Point[][] grid, List<Point> line) {

		StringBuffer sb = new StringBuffer();
		// upper border
		for(int x=0; x<grid.length*2 + 1; x++) {
			 sb.append("+");
        }
        sb.append("\n");
		
        // content
        for(int y=0; y<grid[0].length; y++) {
			
			sb.append("+");
			for(int x=0; x<grid.length; x++) {
				if (x != 0) {
                    sb.append("|");
                }
				sb.append(line.contains(grid[x][y]) ? "X" : " ");
			}
			sb.append("+");
			sb.append("\n");
		}
		
		// lower border
		for(int x=0; x<grid.length*2 + 1; x++) {
			sb.append("+");
		}
		sb.append("\n");
		
		System.out.println(sb.toString());
	}
	

}
