with Ada.Numerics.Elementary_Functions;
with Ada.Numerics.Real_Arrays;
with Ada.Text_IO; use Ada.Text_IO;
with Agpl; use Agpl;
with Agpl.Drawing.Buffer;
with Agpl.Drawing.Figures;
with Agpl.Gdk.Managed.Drawing_Area;
with Agpl.Trace; use Agpl.Trace;
with Agpl.Types;
with Interfaces.C; use Interfaces;
with Gnat.Sockets; use Gnat.Sockets;

procedure Ekfvlocgui is

   Port : constant := 6976;
   Sock : Socket_Type;

   Cli_Sock  : Socket_Type;
   Cli_Addr  : Sock_Addr_Type;
   Cli_Strm  : Stream_Access;

   Draw : Agpl.Drawing.Buffer.Object;

   Colors : constant array (Positive range <>) of
     Types.Rgb_Triplet := ((168, 168, 168), (0, 0, 255), (255, 0, 0));

   Canvas : Agpl.Gdk.Managed.Drawing_Area.Handle :=
     Agpl.Gdk.Managed.Drawing_Area.Show (Draw, "ekfvloc");

begin
   Create_Socket (Sock);
   Bind_Socket (Sock, (Family_Inet, Inet_Addr ("127.0.0.1"), Port));
   Listen_Socket (Sock);

   while True loop
      begin
         Put_Line ("Waiting for connection...");
         Accept_Socket (Sock, Cli_Sock, Cli_Addr);
         Put_Line ("Client connected!");

         Cli_Strm := Stream (Cli_Sock);

         while True loop
            Draw.Clear;

            --  REGIONS
            Draw.Set_Color (Colors (1), 0);
            declare
               Count : constant Integer := Integer (C.Int'Input (Cli_Strm));
            begin
               Put_Line ("Regions:" & Count'Img);
               for J in 1 .. Count loop
                  declare
                     use Ada.Numerics.Elementary_Functions;
                     Rho0 : constant Float := Float (C.Double'Input (Cli_Strm));
                     Phi0 : constant Float := Float (C.Double'Input (Cli_Strm));
                     Rho1 : constant Float := Float (C.Double'Input (Cli_Strm));
                     Phi1 : constant Float := Float (C.Double'Input (Cli_Strm));
                  begin
                     Draw.Draw_Line (0.0, 0.0, Rho0 * Cos (Phi0), Rho0 * Sin (Phi0));
                     Draw.Draw_Line (0.0, 0.0, Rho1 * Cos (Phi1), Rho1 * Sin (Phi1));
                  end;
               end loop;
            end;

            --  SPLITS
            Draw.Set_Color (Colors (2), 0);
            declare
               Count : constant Integer := Integer (C.Int'Input (Cli_Strm));
            begin
               Put_Line ("Splits:" & Count'Img);
               for J in 1 .. Count loop
                  declare
                     use Ada.Numerics.Elementary_Functions;
                     Rho0 : constant Float := Float (C.Double'Input (Cli_Strm));
                     Phi0 : constant Float := Float (C.Double'Input (Cli_Strm));
                     Rho1 : constant Float := Float (C.Double'Input (Cli_Strm));
                     Phi1 : constant Float := Float (C.Double'Input (Cli_Strm));
                  begin
                     Draw.Draw_Line (Rho0 * Cos (Phi0), Rho0 * Sin (Phi0),
                                     Rho1 * Cos (Phi1), Rho1 * Sin (Phi1));

                     Draw.Draw_Line (Rho0 * Cos (Phi0) * 0.5, Rho0 * Sin (Phi0) * 0.5,
                                     Rho0 * Cos (Phi0), Rho0 * Sin (Phi0));
                     Draw.Draw_Line (Rho1 * Cos (Phi1) * 0.5, Rho1 * Sin (Phi1) * 0.5,
                                     Rho1 * Cos (Phi1), Rho1 * Sin (Phi1));

                  end;
               end loop;
            end;

            --  MATCHES
            Draw.Set_Color (Colors (3), 0);
            declare
               Count : constant Integer := Integer (C.Int'Input (Cli_Strm));
            begin
               Put_Line ("Matches:" & Count'Img);
               for J in 1 .. Count loop
                  declare
                     use Ada.Numerics.Elementary_Functions;
                     Rho0 : constant Float := Float (C.Double'Input (Cli_Strm));
                     Phi0 : constant Float := Float (C.Double'Input (Cli_Strm));
                     Rho1 : constant Float := Float (C.Double'Input (Cli_Strm));
                     Phi1 : constant Float := Float (C.Double'Input (Cli_Strm));
                  begin
                     Draw.Draw_Line (Rho0 * Cos (Phi0), Rho0 * Sin (Phi0),
                                     Rho1 * Cos (Phi1), Rho1 * Sin (Phi1));
                  end;
               end loop;
            end;

            --  COVARIANCE
            declare
               use Ada.Numerics.Real_Arrays;
               Cov : Real_Matrix (1 .. 3, 1 .. 3);
               type Fix is delta 0.00001 digits 18;
            begin
               Put_Line ("Covariance:");
               for I in Cov'Range (1) loop
                  for J in Cov'Range (2) loop
                     Cov (I, J) := Float (C.Double'Input (Cli_Strm));
                     begin
                        Put (Fix (Cov (I, J))'Img);
                     exception
                        when others =>
                           Put ("???????");
                     end;
                  end loop;
                  New_Line;
               end loop;

               Draw.Set_Color ((0, 0, 50), 0);
               Agpl.Drawing.Figures.Create_Bivariate_Ellipse
                 ((0.0, 0.0),
                  (1 => (Cov (1, 1), Cov (1, 2)),
                   2 => (Cov (2, 1), Cov (2, 2)))).Draw (Draw);
            end;

            Canvas.Clear;
            Canvas.Append (Draw);
            Canvas.Redraw;
         end loop;
      exception
         when E : Socket_Error =>
            Put_Line ("Conn problem: " & Report (E));
         when E : others =>
            Put_Line ("Loop: " & Report (E));
      end;
   end loop;

exception
   when E : others =>
      Put_Line ("Main: " & Report (E));
end Ekfvlocgui;
