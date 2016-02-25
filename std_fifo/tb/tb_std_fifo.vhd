library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

entity tb_std_fifo is
end tb_std_fifo;

architecture test of tb_std_fifo is
    -- 10 MHz -> 100 ns period. Duty cycle = 1/2.
    constant CLK_PERIOD      : time := 100 ns;
    constant CLK_HIGH_PERIOD : time := 50 ns;
    constant CLK_LOW_PERIOD  : time := 50 ns;

    signal clk   : std_logic := '0';
    signal reset : std_logic := '0';

    signal sim_finished : boolean := false;

    -- std_fifo ---------------------------------------------------------------
    constant DATA_WIDTH : positive := 8;
    constant FIFO_DEPTH : positive := 8;

    signal clr      : std_logic                                                                := '0';
    signal write_en : std_logic                                                                := '0';
    signal data_in  : std_logic_vector(DATA_WIDTH - 1 downto 0)                                := (others => '0');
    signal read_en  : std_logic                                                                := '0';
    signal data_out : std_logic_vector(DATA_WIDTH - 1 downto 0)                                := (others => '0');
    signal empty    : std_logic                                                                := '0';
    signal full     : std_logic                                                                := '0';
    signal usedw    : std_logic_vector(integer(ceil(log2(real(FIFO_DEPTH + 1)))) - 1 downto 0) := (others => '0');

begin
    clk_generation : process
    begin
        if not sim_finished then
            clk <= '1';
            wait for CLK_HIGH_PERIOD;
            clk <= '0';
            wait for CLK_LOW_PERIOD;
        else
            wait;
        end if;
    end process clk_generation;

    std_fifo_inst : entity work.std_fifo
        generic map(DATA_WIDTH => DATA_WIDTH,
                    FIFO_DEPTH => FIFO_DEPTH)
        port map(
            clk      => clk,
            reset    => reset,
            clr      => clr,
            write_en => write_en,
            data_in  => data_in,
            read_en  => read_en,
            data_out => data_out,
            empty    => empty,
            full     => full,
            usedw    => usedw);

    sim : process
        procedure async_reset is
        begin
            wait until rising_edge(clk);
            wait for CLK_PERIOD / 4;
            reset <= '1';

            wait for CLK_PERIOD / 2;
            reset <= '0';
        end procedure async_reset;

        procedure sync_clr is
        begin
            wait until falling_edge(clk);
            clr <= '1';

            wait until falling_edge(clk);
            clr <= '0';
        end procedure sync_clr;

        procedure push(constant val : in natural) is
        begin
            wait until falling_edge(clk);
            write_en <= '1';
            data_in  <= std_logic_vector(to_unsigned(val, data_in'length));

            wait until falling_edge(clk);
            write_en <= '0';
            data_in  <= (others => '0');
        end procedure push;

        procedure pop is
        begin
            wait until falling_edge(clk);
            read_en <= '1';

            wait until falling_edge(clk);
            read_en <= '0';
        end procedure pop;

        procedure push_pop(constant val : in natural) is
        begin
            wait until falling_edge(clk);
            write_en <= '1';
            data_in  <= std_logic_vector(to_unsigned(val, data_in'length));
            read_en  <= '1';

            wait until falling_edge(clk);
            write_en <= '0';
            data_in  <= (others => '0');
            read_en  <= '0';
        end procedure push_pop;

        procedure wait_clock_cycles(constant count : in positive) is
        begin
            wait for count * CLK_PERIOD;
        end procedure wait_clock_cycles;

    begin
        -- async reset
        async_reset;

        wait_clock_cycles(10);

        -- push
        for i in 1 to FIFO_DEPTH loop
            push(i);
        end loop;

        wait_clock_cycles(10);

        -- pop
        for i in 1 to FIFO_DEPTH loop
            pop;
        end loop;

        wait_clock_cycles(10);

        -- pushpop
        push(FIFO_DEPTH + 1);
        for i in 2 to FIFO_DEPTH loop
            push_pop(FIFO_DEPTH + i);
        end loop;
        pop;

        wait_clock_cycles(10);

        -- sync clr
        sync_clr;

        wait_clock_cycles(10);

        sim_finished <= true;
        wait;
    end process sim;

end architecture test;
