function univInterface(choice)
        eval(choice);

end
function all()
    readPorts;
    writePorts;
    show;
    description;
end
function readPorts()
    block = find_system(gcb,...
            'LookUnderMasks','on',...
            'FollowLinks','on','RegExp','on','Name','Out*');
    while ~isempty(block)
        delete_block(block);
    block = find_system(gcb,...
            'LookUnderMasks','on',...
            'FollowLinks','on','RegExp','on','Name','Out*');
    
    end
numRead= str2num(get_param(gcb, 'numRead'));

    for i=1:numRead
        add_block('built-in/Outport',[gcb,['/Out' num2str(i)]]);
    end
end
function writePorts()
    block = find_system(gcb,...
            'LookUnderMasks','on',...
            'FollowLinks','on','RegExp','on','Name','In*');
    while ~isempty(block)
        delete_block(block);
    block = find_system(gcb,...
            'LookUnderMasks','on',...
            'FollowLinks','on','RegExp','on','Name','In*');
    end
    Mux=add_block('built-in/Mux',[gcb,['/InMux']]);
    %,'numinports', 9
    numWrite= str2num(get_param(gcb, 'numWrite'));

    for i=1:numWrite
        block=add_block('built-in/Inport',[gcb,['/In' num2str(i)]]);
      %  add_line(gcb,block. ,Mux, 'autorouting','on')
    end
end
function show()
  en = get_param(gcb,'MaskEnables');
  hide = get_param(gcb,'MaskVisibilities');
   numWrite=str2num(get_param(gcb, 'numWrite'));

   numRead=str2num(get_param(gcb, 'numRead'));
   prompts=get_param(gcb,'MaskPrompts');
   configVars=3;
   posWVars=5;
   posRVars=5;

   
   for i=configVars:configVars+posWVars+1;
       if i<=configVars+numWrite+1
            en{i} = 'on';
            hide{i}='on';
       else
            en{i} = 'off';
            hide{i}='off';
       end
       
    end
   for i=configVars+posWVars+1:configVars+posWVars+posRVars
       if i<configVars+posWVars+numRead+2
            en{i} = 'on';
            hide{i}='on';
       else
            en{i} = 'off';
            hide{i}='off';
       end
       
    end
 set_param(gcb,'MaskEnables',en) 
 set_param(gcb,'MaskVisibilities',hide) 
end

function description()
%#eml
buff=zeros(1,100,'uint8');
get_param(gcb,'dev')
%set_param(gcb,'MaskDescription',descriptions(get_param(gcb,'dev'))) ;

end


