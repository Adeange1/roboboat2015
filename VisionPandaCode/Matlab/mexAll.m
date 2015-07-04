% Edited by James Tripiciano, July 2011
function mexAll()
	dirListing = dir;
	% loop through the files and open. Note that dir also lists the directories, so you have to check for them.
	for d = 1:length(dirListing)
		fileName =dirListing(d).name; % use full path because the folder may not be the active path

		% open your file here 
		if length(strfind(fileName,'.c'))~=0
			try
				[response]=mex(fileName);
			catch exception
				disp([fileName , ' failed to compile']);
        end
    end
end % for-loop
end