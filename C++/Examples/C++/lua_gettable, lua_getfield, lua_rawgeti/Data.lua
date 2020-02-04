int1DimTable = {4, 5, 6}
int2DimTable = { {1, 2, 3}, {4, 5, 6} }
stt1DimTable = {a = 4, b = 5, c = 6} --stt1DimTable = {["a"] = 4, ["b"] = 5, ["c"] = 6}
sttBackground = {r = 0.30, g = 0.10, b = 0}
sttTableWithinTable1 = { ["a"] = 1, ["b"] = {10, 20, 30}, ["c"] = 3 }
sttTableWithinTable2 = { ["a"] = 1, [100] = {10, 20, 30}, ["c"] = 3 }

--~ ql2 = {bid_count = "2" , offer_count = "2", bid = {}, offer = {} }
--~ ql2.bid[1] = 	{price = "15140", quantity = "10"}
--~ ql2.bid[2] = 	{price = "15141", quantity = "11"}
--~ ql2.offer[1] = 	{price = "15150", quantity = "20"}
--~ ql2.offer[2] = 	{price = "15151", quantity = "21"}
ql2 = {
	bid_count = "2",
	offer_count = "2",
	bid = {
		[1] = {
			price = "15140",
			quantity = "10"
		},
		[2] = {
			price = "15141",
			--quantity = "11"
			quantity = nil
		}
	},
	offer = {
		[1] = {
			price = "15150",
			quantity = "20"
		},
		[2] = {
			price = "15151",
			quantity = "21"
		}
	}
}
