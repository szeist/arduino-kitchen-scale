#!/bin/bash

mv CHPLX12-F.Cu.gtl CHPLX12_Top_Copper.cmp
mv CHPLX12-B.Cu.gbl CHPLX12_Bottom_Copper.sol
mv CHPLX12-F.Mask.gts CHPLX12_Top_Soldermask.stc
mv CHPLX12-B.Mask.gbs CHPLX12_Bottom_Soldermask.sts
mv CHPLX12-B.SilkS.gbo CHPLX12_Top_Silkscreen.plc 
mv CHPLX12-Edge.Cuts.gm1 CHPLX12_Outline_Milling.milling
mv CHPLX12_Top_Silkscreen.plc CHPLX12_Bottom_Silkscreen.plc
mv CHPLX12-F.SilkS.gto CHPLX12_Bottom_Silkscreen.pls