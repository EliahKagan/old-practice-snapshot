class GfG {
	String encode(String str)
	{
	    final StringBuilder encoding = new StringBuilder();
	    
	    char prev = str.charAt(0);
	    int count = 1;
	    
	    for (int i = 1; ; ++i) {
	        final boolean done = i == str.length();
	        
	        if (done || str.charAt(i) != prev) {
	            encoding.append(prev).append(count);
	            if (done) return encoding.toString();
	            
	            prev = str.charAt(i);
	            count = 1;
	        }
	        else ++count;
	    }
	}
 }
