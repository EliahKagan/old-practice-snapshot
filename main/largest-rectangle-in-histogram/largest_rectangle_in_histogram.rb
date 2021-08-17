# @param {Integer[]} heights
# @return {Integer}
def largest_rectangle_area(heights)
  max_area = 0
  lefts = []

  heights.push(0).unshift(0).each_with_index do |right_height, right|
    while !lefts.empty? && heights[lefts.last] > right_height
      left = lefts.pop

      width = right
      width -= 1 + lefts.last unless lefts.empty?

      area = heights[left] * width
      max_area = area if max_area < area
    end

    lefts << right
  end

  max_area
end
