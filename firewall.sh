#!/bin/bash

rules_txt="$1"
#cat packets.txt


if [[ -e legit_rules.txt ]]; then
	rm legit_rules.txt
fi
if [[ -e packetsss.txt ]]; then
	rm packetsss.txt
fi

if [[ -e print_shit_out.txt ]]; then
	rm print_shit_out.txt
fi

cat > packetsss.txt


#comment="#" make parameter "pattern"
not_only_comment=".+#.*"

grep -o '^[^#]*' $rules_txt > legit_rules.txt

cat legit_rules.txt | sort | uniq > legit_rules_uniq.txt

while read line; do
	IFS=',' read -r -a fields <<< "$line"
	#echo "new rule"
	#echo "${fields[0]}"
	#echo "${fields[1]}"
	#echo "${fields[2]}"
	#echo "${fields[3]}"
data=$(cat packetsss.txt | \
       ./firewall.exe "${fields[0]}" 2>/dev/null | \
       ./firewall.exe "${fields[1]}" 2>/dev/null| \
       ./firewall.exe "${fields[2]}" 2>/dev/null| \
       ./firewall.exe "${fields[3]}" 2>/dev/null)

echo "$data" >> temp.txt
#./firewall.exe "${fields[0]}" < packets.txt
#./firewall.exe "${fields[1]}" < packetsss.txt 2>/dev/null
#./firewall.exe "${fields[1]}" 2>/dev/null 

#./firewall.exe "${fields[1]}" < temp_out0.txt > temp_out1.txt
#| ./firewall.exe "${fields[2]}" |./firewall.exe "${fields[3]}"

#cat temp_out0.txt | grep 'src-ip'
#cat | ./firewall.exe "${fields[0]}" >> print_shit_out.txt #| ./firewall.exe "${fields[1]}" |\
	#./firewall.exe "${fields[2]}" | ./firewall.exe "${fields[3]}" #>> print_shit_out.txt 
done < legit_rules_uniq.txt


cat temp.txt | sort | uniq | tr -d " \t" > final3.txt
#cat print_test_out.txt
rm -f temp.txt packetsss.txt legit_rules_uniq.txt legit_rules.txt
#echo `cat print_shit_out.txt | sort | uniq`



