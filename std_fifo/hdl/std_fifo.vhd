-- Slightly modified from original source from daniel@deathbylogic.com:
--     http://www.deathbylogic.com/2013/07/vhdl-standard-fifo/
--
-- Added usedw output to know how many words are currently stored in the fifo.
-- Added async reset port (useful for some designs)
-- Reset internal memory as well when receiving async reset or sync clr.

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

entity std_fifo is
    generic(
        DATA_WIDTH : positive := 8;
        FIFO_DEPTH : positive := 256
    );
    port(
        clk      : in  std_logic;
        reset    : in  std_logic;
        clr      : in  std_logic;
        write_en : in  std_logic;
        data_in  : in  std_logic_vector(DATA_WIDTH - 1 downto 0);
        read_en  : in  std_logic;
        data_out : out std_logic_vector(DATA_WIDTH - 1 downto 0);
        empty    : out std_logic;
        full     : out std_logic;
        usedw    : out std_logic_vector(integer(ceil(log2(real(FIFO_DEPTH + 1)))) - 1 downto 0)
    );
end std_fifo;

architecture behavioral of std_fifo is
begin

    -- memory pointer process
    fifo_proc : process(clk, reset)
        type fifo_memory is array (0 to FIFO_DEPTH - 1) of std_logic_vector(DATA_WIDTH - 1 downto 0);
        variable memory : fifo_memory;

        variable head : natural range 0 to FIFO_DEPTH - 1;
        variable tail : natural range 0 to FIFO_DEPTH - 1;

        variable fill_level : natural range 0 to FIFO_DEPTH;

        variable looped : boolean;
    begin
        if reset = '1' then
            head       := 0;
            tail       := 0;
            fill_level := 0;
            looped     := false;
            full       <= '0';
            empty      <= '1';
        elsif rising_edge(clk) then
            if clr = '1' then
                head       := 0;
                tail       := 0;
                fill_level := 0;
                looped     := false;
                full       <= '0';
                empty      <= '1';
            else
                if (read_en = '1') then
                    if ((looped = true) or (head /= tail)) then
                        -- update data output
                        data_out <= memory(tail);

                        fill_level := fill_level - 1;

                        -- update tail pointer as needed
                        if (tail = FIFO_DEPTH - 1) then
                            tail := 0;

                            looped := false;
                        else
                            tail := tail + 1;
                        end if;

                    end if;
                end if;

                if (write_en = '1') then
                    if ((looped = false) or (head /= tail)) then
                        -- write data to memory
                        memory(head) := data_in;

                        fill_level := fill_level + 1;

                        -- increment head pointer as needed
                        if (head = FIFO_DEPTH - 1) then
                            head := 0;

                            looped := true;
                        else
                            head := head + 1;
                        end if;
                    end if;
                end if;

                usedw <= std_logic_vector(to_unsigned(fill_level, usedw'length));

                -- update empty and full flags
                if (head = tail) then
                    if looped then
                        full <= '1';
                    else
                        empty <= '1';
                    end if;
                else
                    empty <= '0';
                    full  <= '0';
                end if;
            end if;
        end if;
    end process;

end behavioral;
