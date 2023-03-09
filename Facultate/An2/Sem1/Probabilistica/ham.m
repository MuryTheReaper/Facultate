function retval = ham ()
  
  #atentie valorile fisierelor sunt inversate din functia spam.m
  
  spamWords = strsplit(fileread('Extras/keywords_ham.txt'), ' ');
  spamUniqueWords = unique(spamWords);
  spamUniqueWords = spamUniqueWords(2:end);
  
  hamWords = strsplit(fileread('Extras/keywords_spam.txt'), ' ');
  hamL = length(hamWords);
  
  emailOne = strsplit(fileread('Extras/email1.txt'), ' ');
  
  freq = [];
  spamL = length(spamWords);
  spamUL = length(spamUniqueWords);
  
  for(i = 1:spamUL)
    counter = 0;
    
    for(j = 1:spamL) 
      counter += strcmp(spamUniqueWords(i), spamWords(j));
    endfor
    
    freq = [freq, counter/spamL];
  endfor
  
  for(i = 1:spamUL)
    counter = 0;
    
    for(j = 1: length(emailOne))
      counter += strcmp(spamUniqueWords(i), emailOne(j));
    endfor
    
    if counter == 0 
      freq(i) = 1 - freq(i);
    endif
   
  endfor
  
  spamP = prod(freq)*spamL/(spamL + hamL)
  
  
endfunction
