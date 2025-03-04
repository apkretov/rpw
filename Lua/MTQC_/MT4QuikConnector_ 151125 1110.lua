require("MT4QuikConnector");

mstrFutures = "SRZ5";
mstrPricesForQuik = "";

-- Shape = {area = 0} -- Meta class ------------------------------------------------------------------

-- function Shape:new (o, side) -- Base class method new
   -- o = o or {}
   -- setmetatable(o, self)
   -- self.__index = self
   -- side = side or 0
   -- self.area = side*side;
   -- return o
-- end

-- function Shape:printArea () -- Base class method printArea
   -- message("The area is " .. self.area);
-- end

-- myshape = Shape:new(nil, 10) -- Creating an object
-- myshape:printArea()

-- Rectangle = {area = 0, length = 0, breadth = 0} -- Meta class ------------------------------------------------------------------

-- function Rectangle:new (o, length, breadth) -- Derived class method new
   -- o = o or {}
   -- setmetatable(o, self)
   -- self.__index = self
   -- self.length = length or 0
   -- self.breadth = breadth or 0
   -- self.area = length*breadth;
   -- return o
-- end

-- function Rectangle:printArea () -- Derived class method printArea
   -- message("The area of Rectangle is " .. self.area);
-- end

-- r = Rectangle:new(nil, 10, 20)
-- message(tostring(r.length));
-- r:printArea()

objects = {pricesForQuik = ""}; -- Meta class ------------------------------------------------------------------

function TotalNetGet()
	local intTotalNet = -1234567890;
	--local strFutures = "SRZ5";
	-- for i = 0, getNumberOf("FUTURES_CLIENT_HOLDING") - 1 do -- Перебирает строки таблицы "Позиции по клиентским счетам (фьючерсы)", ищет Текущие чистые позиции по инструменту "RIH5"
	   -- if getItem("FUTURES_CLIENT_HOLDING", i).sec_code == strFutures then -- ЕСЛИ строка по нужному инструменту
			-- intTotalNet = getItem("FUTURES_CLIENT_HOLDING", i).totalnet;
			-- break;
	   -- end;
	-- end;
	if getNumberOf("FUTURES_CLIENT_HOLDING") > 0 then intTotalNet = getItem("FUTURES_CLIENT_HOLDING", 1).totalnet; end -- I trade only one futures for the time being. Otherwise uncomment the procedure above.
	return(intTotalNet);
end

function srvMessageToQuik(strMessage)
	message(strMessage);
	mstrPricesForQuik = strMessage;
end

function main() -- с периодичность в 1 миллисекунду проверяет не пришла ли команда из C#
	Run = true; -- Флаг поддержания работы скрипта
	MT4QuikConnector.StartQuikServer();
	while Run do
		sleep(100);
	end
end

function OnStop()
	Run = false; -- Завершает цикл while, следовательно завершается main() и сам скрипт останавливается
	--message("Quit Quik to stop MT4QuikConnector.")
	message("Quit Quik to quit MT4QuikConnector.")
end

-- function OnQuote(class, sec )
	-- if class == "SPBFUT" and sec == mstrFutures then
		-- PriceGet();
	-- end
-- end