#!/usr/bin/env ruby
$VERBOSE = true

status = 0

ARGV.each do |path|
  begin
    lines = words = chars = 0

    File.open(path, 'r') do |file|
      file.each_line do |line|
        lines += 1
        words += line.split.length
        chars += line.length
      end
    end

    puts(" #{lines} #{words} #{chars} #{path}")
  rescue SystemCallError => e
    $stderr.puts("#{$PROGRAM_NAME}: #{path}: #{e.message}")
    status = 1
  end
end

exit status
