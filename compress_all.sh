#!/bin/bash

COMPRESSOR="./bmp_to_bmc"
EXTENSION=".bmc"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Counters
total_files=0
successful=0
failed=0
total_original_size=0
total_compressed_size=0

if [ ! -f "$COMPRESSOR" ]; then
    echo -e "${RED}no '$COMPRESSOR'!${NC}"
    echo "compile first!!!"
    exit 1
fi

if [ ! -x "$COMPRESSOR" ]; then
    chmod +x "$COMPRESSOR"
fi

if [ $# -eq 0 ]; then
    echo "use: $0 <directory>"
    exit 1
fi

TARGET_DIR="$1"

if [ ! -d "$TARGET_DIR" ]; then
    echo -e "${RED}fail '$TARGET_DIR' not found!${NC}"
    exit 1
fi

echo -e "${BLUE}compress lk logo in: $TARGET_DIR${NC}"
echo ""

while IFS= read -r -d '' bmp_file; do
    ((total_files++))
    
    file_size=$(stat -c%s "$bmp_file" 2>/dev/null || stat -f%z "$bmp_file" 2>/dev/null)
    total_original_size=$((total_original_size + file_size))
    
    output_file="${bmp_file%.bmp}${EXTENSION}"
    
    echo -e "${BLUE}[$total_files]${NC} compress: $bmp_file"
    echo -e "size: $(numfmt --to=iec-i --suffix=B $file_size 2>/dev/null || echo "$file_size bytes")"
    
	if "$COMPRESSOR" "$bmp_file" "$output_file" > /dev/null 2>&1; then
		compressed_size=$(stat -c%s "$output_file" 2>/dev/null || stat -f%z "$output_file" 2>/dev/null)
		total_compressed_size=$((total_compressed_size + compressed_size))
		
		ratio=$(awk "BEGIN {printf \"%.1f\", ($compressed_size * 100.0) / $file_size}")
		
		echo -e "    ${GREEN}has compress:${NC} $output_file"
		echo -e "    ${GREEN}size: $(numfmt --to=iec-i --suffix=B $compressed_size 2>/dev/null || echo "$compressed_size bytes") (${ratio}%)${NC}"
		
		if rm "$bmp_file"; then
			echo -e "    ${GREEN}remove original ${NC}"
			((successful++))
		else
			echo -e "    ${RED}fail rempove original ${NC}"
			((failed++))
		fi
	else
		echo -e "    ${RED}fail compress ${NC}"
		((failed++))
	fi
    
    echo ""
    
done < <(find "$TARGET_DIR" -type f \( -iname "*.bmp" \) -print0)

echo "=========================================="
echo -e "${BLUE}SUMMARY${NC}"
echo "=========================================="
echo "source: $total_files"
echo "pass: $successful"
echo "fail: $failed"
echo ""

if [ $successful -gt 0 ]; then
    echo "original: $(numfmt --to=iec-i --suffix=B $total_original_size 2>/dev/null || echo "$total_original_size bytes")"
    echo "new: $(numfmt --to=iec-i --suffix=B $total_compressed_size 2>/dev/null || echo "$total_compressed_size bytes")"
    
    if [ $total_original_size -gt 0 ]; then
        overall_ratio=$(awk "BEGIN {printf \"%.1f\", ($total_compressed_size * 100.0) / $total_original_size}")
        saved=$((total_original_size - total_compressed_size))
        echo "overall: ${overall_ratio}%"
        echo "save: $(numfmt --to=iec-i --suffix=B $saved 2>/dev/null || echo "$saved bytes")"
    fi
fi

if [ $total_files -eq 0 ]; then
    echo -e "${YELLOW}no bmp.${NC}"
    exit 0
fi

if [ $failed -gt 0 ]; then
    exit 1
fi

exit 0