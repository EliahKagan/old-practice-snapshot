n = gets.to_f
pos, neg, zero = 0, 0, 0

gets.split(' ').map(&:to_i).each do |k|
    if k > 0
        pos += 1
    elsif k < 0
        neg += 1
    else
        zero += 1
    end
end

printf "%f\n%f\n%f\n", pos / n, neg / n, zero / n
