function ardInterface(choice)
%sum(cell2mat(strfind(get_param(gcb,'MaskValues'),'Motor')))
    eval(choice);

end
function all()

    clearPorts;
    inConns=0;
    outConns=0;
    [inConns outConns]=digitalPorts(inConns,outConns);
    [inConns outConns]=analogPorts(inConns,outConns);
    sfun(inConns,outConns);
    connections(inConns,outConns);
    %show;
    %description;
end
function clearPorts()

    block = find_system(gcb,'LookUnderMasks','on','FollowLinks','on','RegExp','on','Name','/*Mux');
    while ~isempty(block)
        delete_block(block);
    block = find_system(gcb,'LookUnderMasks','on','FollowLinks','on','RegExp','on','Name','/*Mux');
    end
    delete_block(block);
    lines = find_system(gcb,'FindAll', 'on','LookUnderMasks','on','type', 'line');
    delete_line(lines);
end

function [inConns outConns]=digitalPorts(inConns,outConns)
    for i=2:13 
        temp=get_param(gcb,['PinConfig' num2str(i)] );
        if strcmp(temp,'Unused')==0  
            if ~isempty(strfind(temp, 'Write')) || ~isempty(strfind(temp, 'Motor'))
                block = find_system(gcb,...
                    'LookUnderMasks','on',...
                    'FollowLinks','on','RegExp','on','Name',['/*@DPin' num2str(i)]);
                if  sum(strcmp(get_param(block, 'Name'),[temp '@DPin' num2str(i)]))==0 || isempty(block)
                     delete_block(block)
                     pos = [10 20+10*inConns 20 30+10*inConns];
                     add_block('built-in/Inport',[gcb,['/' temp '@DPin' num2str(i)]],'Position',pos);
                 end
                 inConns=inConns+1;
                 
            else
                
                 block = find_system(gcb,...
                    'LookUnderMasks','on',...
                    'FollowLinks','on','RegExp','on','Name',['/*@DPin' num2str(i)]);
                if  sum(strcmp(get_param(block, 'Name'),[temp '@DPin' num2str(i)]))==0 || isempty(block)
                    delete_block(block)
                    pos = [250 20+10*outConns 260 30+10*outConns];
                    add_block('built-in/Outport',[gcb,['/' temp '@DPin' num2str(i)]],'Position',pos);
                 end
                 outConns=outConns+1;
            end
        else  %unused,delete old blocks]
            delete_block(find_system(gcb,'LookUnderMasks','on','FollowLinks','on','FindAll', 'on','RegExp','on','Name',['/*@DPin' num2str(i)]));
        end
    end
end

function [inConns outConns]=analogPorts(inConns,outConns)

    for i=0:5      
        temp=get_param(gcb,['ApinConfig' num2str(i)] );
        if strcmp(temp,'Unused')==0  
            if ~isempty(strfind(temp, 'Write'))
                block = find_system(gcb,...
                    'LookUnderMasks','on',...
                    'FollowLinks','on','RegExp','on','Name',['/*@APin' num2str(i)]);
                 if  sum(strcmp(get_param(block, 'Name'),[temp '@APin' num2str(i)]))==0 || isempty(block)
                     delete_block(block)
                     pos = [10 20+10*inConns 20 30+10*inConns];
                     add_block('built-in/Inport',[gcb,['/' temp '@APin' num2str(i)]],'Position',pos);
                 end
                 inConns=inConns+1;
                 
            else
                
                 block = find_system(gcb,...
                    'LookUnderMasks','on',...
                    'FollowLinks','on','RegExp','on','Name',['/*@APin' num2str(i)]);
                 if  sum(strcmp(get_param(block, 'Name'),[temp '@APin' num2str(i)]))==0 || isempty(block)
                     delete_block(block)
                     pos = [250 20+10*outConns 260 30+10*outConns];
                     add_block('built-in/Outport',[gcb,['/' temp '@APin' num2str(i)]],'Position',pos);
                 end
                 outConns=outConns+1;
            end
        else  %unused,delete old blocks]
            delete_block(find_system(gcb,'LookUnderMasks','on','FollowLinks','on','FindAll', 'on','RegExp','on','Name',['/*@APin' num2str(i)]));
        end
    end
end
function sfun(inConns,outConns)

conf='';
    for i=2:13 %Digitals
        temp=get_param(gcb,['PinConfig' num2str(i)] );
        if strcmp(temp,'Unused')
        elseif strcmp(temp,'Encoder (with pin 4)')
            conf=[conf ':D' (i+48) 'I']; %#ok<*AGROW>
        elseif strcmp(temp,'Encoder (with pin 5)')
            conf=[conf ':D' (i+48) 'I']; %#ok<*AGROW>
        elseif strcmp(temp,'PWM Write')
            conf=[conf ':D' (i+48) 'P'];
        elseif strcmp(temp,'Logic Read (floating)')
            conf=[conf ':D' (i+48) 'F'];
        elseif strcmp(temp,'Logic Read (pulled high)')
            conf=[conf ':D' (i+48) 'H'];
        elseif strcmp(temp,'Logic Write')
            conf=[conf ':D' (i+48) 'O'];
        elseif strcmp(temp,'DC Motor #1')
            conf=[conf ':M' (1+48) 'M'];
        elseif strcmp(temp,'DC Motor #2')
            conf=[conf ':M' (2+48) 'M'];
        elseif strcmp(temp,'DC Motor #3')
            conf=[conf ':M' (3+48) 'M'];
        elseif strcmp(temp,'DC Motor #4')
            conf=[conf ':M' (4+48) 'M'];
        elseif strcmp(temp,'Stepper Motor #1')
            conf=[conf ':M' (1+48) 'T'];
        elseif strcmp(temp,'Stepper Motor #2')
            conf=[conf ':M' (2+48) 'T'];
        elseif strcmp(temp,'Servo Motor #1')
            conf=[conf ':M' (9+48) 'S'];
        elseif strcmp(temp,'Servo Motor #2')
            conf=[conf ':M' (10+48) 'S'];
        end
    end
    for i=0:5 %Analogs
        temp=get_param(gcb,['ApinConfig' num2str(i)] );
        if strcmp(temp,'Unused')
            
        elseif strcmp(temp,'Analog Read')
            conf=[conf ':A' num2str(i) 'A'];
        end
    end
    delete_block(find_system(gcb,'LookUnderMasks','on','FollowLinks','on','RegExp','on','Name','/*ardController'));
    pos = [100 30 170 70];
    conf=['''[' conf ']'' ''' num2str(inConns) ''' ''' num2str(outConns) ''''] %#ok<NOPRT>
    add_block('built-in/S-Function',[gcb, '/ardController'],'function name','ardController','parameters',conf,'Position',pos);

end
function connections(inConns,outConns)
%MuxBlock = sprintf('%s/Mux',CB);


if inConns>0
    MuxPos = [60 40 80 60];
    add_block('built-in/Mux',[gcb, '/InMux'],'Inputs',num2str(inConns),'Position',MuxPos,'ShowName','off');
    add_line(gcb,'InMux/1','ardController/1');
else
    delete_block(find_system(gcb,'LookUnderMasks','on','FollowLinks','on','Name','InMux'));   
end

if outConns>0
    MuxPos = [190 40 210 60];
    add_block('built-in/DeMux',[gcb, '/OutMux'],'Outputs',num2str(outConns),'Position',MuxPos,'ShowName','off');
    add_line(gcb,'ardController/1','OutMux/1');
else
    delete_block(find_system(gcb,'LookUnderMasks','on','FollowLinks','on','Name','OutMux'));
end
ipos=1;
opos=1;
for i=2:13 %Digitals
    temp=get_param(gcb,['PinConfig' num2str(i)] );
    if strcmp(temp,'Unused')==0  
        if ~isempty(strfind(temp, 'Write')) || ~isempty(strfind(temp, 'Motor'))
            add_line(gcb,[temp '@DPin' num2str(i) '/1'],['InMux/' num2str(ipos)]);
            ipos=ipos+1;
        else
            add_line(gcb,['OutMux/' num2str(opos)],[temp '@DPin' num2str(i) '/1']);
            opos=opos+1;
        end
    end
end
for i=0:5 %Analogs
    temp=get_param(gcb,['ApinConfig' num2str(i)] );
    if strcmp(temp,'Unused')==0  
        if ~isempty(strfind(temp, 'Write'))
            add_line(gcb,[temp '@APin' num2str(i) '/1'],['InMux/' num2str(ipos)]);
            ipos=ipos+1;
        else
            add_line(gcb,['OutMux/' num2str(opos)],[temp '@APin' num2str(i) '/1']);
            opos=opos+1;
        end
    end
end


end
function clearAll() %#ok<DEFNU>
'pow'
    all=find_system(gcb,'FollowLinks','on','LookUnderMasks','all','RegExp','on','Name','/*@*')
    %delete_block(all(2:end));
end


